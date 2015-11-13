#!/usr/bin/perl

use strict; use warnings;
no warnings 'recursion';
no warnings 'experimental';
use 5.14.0;
use Switch::Plain;
use sigtrap 'handler' => \&handle_int, 'INT';
use Time::HiRes qw(time);
use Carp;
$| = 1;


#    Tasks n°   1   2   3   4   5   6   7   8
my @tasks = ([ 35, 12, 25,  6, 76, 56, 54, 25 ],  # Mach A
             [ 26, 15, 41, 15, 65, 68, 42, 32 ],  # Mach B
             [ 13, 19, 21, 25, 51, 42, 28, 31 ]); # Mach C

my ($global_min, $best_node, $bsup, $binf) = (1 << 32, undef, 0, 1 << 32);
my $visited = 0;

my ($approx, $rapport, $nb_node) = ($ARGV[0] ? 1 : 0, $ARGV[0] || 0.01, $ARGV[1] || 3_000_000);

{
    package node;
    use List::Util qw(min max);

    sub new {
        my ($class, $task, $done, $timeA, $timeB, $timeC) = @_;
        my $self = {};
        $self->{task} = $task;
        $self->{done} = $done;
        $self->{timeA} = $timeA;
        $self->{timeB} = $timeB;
        $self->{timeC} = $timeC;
        $self = bless($self, $class);
        $self->calc_b1_plus; $self->calc_b2;
        $self->calc_b3;
        $visited++;
        return $self;
    }

    # some getters
    sub b1 {return shift->{b1} }
    sub b2 {return shift->{b2} }
    sub b3 {return shift->{b3} }
    sub done { return shift->{done} }
    sub timeC { return shift->{timeC} }
    sub is_leaf {return ! @{shift->{task}} }

    sub b {
        my $self = shift; 
        return max($self->b1, $self->b2, $self->b3);
    }

    # bound
    sub calc_b1 {
        my $self = shift;
        my ($b_A, $b_B, $b_C) = ($self->{timeA}, $self->{timeB}, $self->{timeC});
        my ($minA, $minB) = (1 << 32, 1 << 32);
        foreach my $index (@{$self->{task}}) {
            $b_A += $tasks[0]->[$index];
            $b_B += $tasks[1]->[$index];
            $b_C += $tasks[2]->[$index];
            $minA = $tasks[1]->[$index] + $tasks[2]->[$index]
                if ($tasks[1]->[$index] + $tasks[2]->[$index] < $minA);
            $minB = $tasks[2]->[$index]
                if ($tasks[2]->[$index] < $minB);
        } 
        $b_A += $minA; $b_B += $minB;
        $self->{b1} =  max($b_A, $b_B, $b_C);
        return $self->{b1};
    }
    sub calc_b1_plus {
        my $self = shift;
        my ($b_A, $b_B, $b_C) = ($self->{timeA}, 0, 0);
        my ($minA, $minB, $mindA, $mindB, $mindAB) = (1<<32, 1<<32, 1<<32, 1<<32, 1<<32);
        foreach my $index (@{$self->{task}}) {
            $b_A += $tasks[0]->[$index];
            $b_B += $tasks[1]->[$index];
            $b_C += $tasks[2]->[$index];
            $mindA = $tasks[0]->[$index] if $tasks[0]->[$index] < $mindA;
            $mindB = $tasks[1]->[$index] if $tasks[1]->[$index] < $mindB;
            $mindAB = $tasks[0]->[$index] + $tasks[1]->[$index] 
                if  $tasks[0]->[$index] + $tasks[1]->[$index] < $mindAB;
            $minA = $tasks[1]->[$index] + $tasks[2]->[$index]
                if ($tasks[1]->[$index] + $tasks[2]->[$index] < $minA);
            $minB = $tasks[2]->[$index]
                if ($tasks[2]->[$index] < $minB);
        } 
        $b_B += max ($self->{timeB}, $self->{timeA} + $mindA);
        $b_C += max ($self->{timeC}, $self->{timeB} + $mindB,  $self->{timeA} + $mindAB);
        $b_A += $minA; $b_B += $minB;
        $self->{b1} =  max($b_A, $b_B, $b_C);
        return $self->{b1};
    }
    sub calc_b2 {
        my $self = shift;
        my ($b2, $timeA) = (0, $self->{timeA});
        foreach my $index (@{$self->{task}}) {
            my $b2_cur = $timeA + $tasks[0]->[$index] + $tasks[1]->[$index] +
                $tasks[2]->[$index];
            foreach my $elem (@{$self->{task}}) {
                next if $elem == $index;
                $b2_cur += min ($tasks[0]->[$elem], $tasks[2]->[$elem]);
            }
            $b2 = $b2_cur if $b2 < $b2_cur;
        }
        $self->{b2} = $b2;
        return $b2;
    }
    sub calc_b3 {
        my $self = shift;
        my ($b3, $timeB, $timeC) = (0, $self->{timeB}, $self->{timeC});
        foreach my $index (@{$self->{task}}) { # sur la machine B
            my $b3_cur = $timeB + $tasks[1]->[$index] + $tasks[2]->[$index];
            foreach my $elem (@{$self->{task}}) {
                next if $elem == $index;
                $b3_cur += min ($tasks[1]->[$elem], $tasks[2]->[$elem]);
            }
            $b3 = $b3_cur if $b3 < $b3_cur;
        }
        my $b3_cur = $timeC;
        foreach my $index (@{$self->{task}}) { # sur la machine C
            $b3_cur += $tasks[2]->[$index];
        }  $b3 = $b3_cur if $b3 < $b3_cur;
        $self->{b3} = $b3;
        return $b3;
    }
    
    # branch
    sub expand {
        my $self = shift;
        my ($i, $task, $done, $timeA, $timeB, $timeC, $b1) = 
            (0, $self->{task}, $self->{done}, $self->{timeA}, 
             $self->{timeB}, $self->{timeC}, $self->{b1});

        foreach my $index (@{$self->{task}}) {
            return if $b1 >= $global_min;
            # calcul les paramètres du nouveau noeud à créer
            splice @{$task}, $i, 1; # retire l'élément à l'index $i du tableau pointé par $task
            my @task = @$task;
            my @done = (@$done, $index);
            my $new_timeA = $timeA + $tasks[0]->[$index];
            my $new_timeB = $new_timeA <= $timeB ? $timeB + $tasks[1]->[$index] :
                $new_timeA + $tasks[1]->[$index];
            my $new_timeC = $new_timeB <= $timeC ? $timeC + $tasks[2]->[$index] :
                $new_timeB + $tasks[2]->[$index];
            # on crée le nouveau noeud
            my $node = new node (\@task, \@done, $new_timeA, $new_timeB, $new_timeC);

            splice @{$task}, $i, 0, $index; # insère $index à l'index $i dans le tableau $task
            $i++; 

            # say "[ " . (join ", ", map { $_ + 1 } @done) . " ]   -> " . $node->b1;

            if ($node->is_leaf) { # Si c'est une feuille, on met à jour le minimum global si besoin
                if ($node->timeC < $global_min) {
                    # say "*** new minimum : " . $node->timeC;
                    $global_min = $node->timeC;
                    $best_node = $node;
                }
		$binf = min($node->timeC, $binf);
                return if $node->timeC == $b1; # si on a atteint la borne inf du noeud courant,
                # pas la peine de brancher sur les autres fils.
                next;
            }
            # FLAG BOUND
	    $binf = min($node->b, $binf);
	    kill 2, $$ if $best_node && (($approx && (($best_node->timeC - $binf)/$binf <= $rapport)) || 
		($visited > $nb_node));
            if ($node->b < $global_min && $node->b <= $bsup) { # on expand (=branch) uniquement si
                # la borne inf est < au minimum atteint
                $node->expand; # le parcours se fait bien en profondeur.
            } 
        }
    }

    sub greedy_expand {
        my $self = shift;
        my ($i, $task, $done, $timeA, $timeB, $timeC, $b1) = 
            (0, $self->{task}, $self->{done}, $self->{timeA}, 
             $self->{timeB}, $self->{timeC}, $self->{b1});

        my @to_expand;
        foreach my $index (@{$self->{task}}) {
            return if $b1 >= $global_min;
            # calcul les paramètres du nouveau noeud à créer
            splice @{$task}, $i, 1; # retire l'élément à l'index $i du tableau pointé par $task
            my @task = @{$task};
            my @done = (@{$done}, $index);
            my $new_timeA = $timeA + $tasks[0]->[$index];
            my $new_timeB = $new_timeA <= $timeB ? $timeB + $tasks[1]->[$index] :
                $new_timeA + $tasks[1]->[$index];
            my $new_timeC = $new_timeB <= $timeC ? $timeC + $tasks[2]->[$index] :
                $new_timeB + $tasks[2]->[$index];
            # on crée le nouveau noeud
            my $node = new node (\@task, \@done, $new_timeA, $new_timeB, $new_timeC);

            splice @{$task}, $i, 0, $index; # insère $index à l'index $i dans le tableau $task
            $i++; 
            
            push @to_expand, $node;

        }

        foreach my $node (sort { $a->b <=> $b->b } @to_expand) {
            
            if ($node->is_leaf) { # Si c'est une feuille, on met à jour le minimum global si besoin
                if ($node->timeC < $global_min) {
                    # say "*** new minimum : " . $node->timeC;
                    $global_min = $node->timeC;
                    $best_node = $node;
                }
		$binf = min($node->timeC, $binf);
                return if $node->timeC == $b1; # si on a atteint la borne inf du noeud courant,
                # pas la peine de brancher sur les autres fils.
                next;
            }
            # FLAG BOUND
	    $binf = min($node->b, $binf);
	    kill 2, $$ if $best_node && (($approx && (($best_node->timeC - $binf)/$binf <= $rapport)) || 
		($visited > $nb_node));
            if ($node->b < $global_min && $node->b <= $bsup) { # on expand (=branch) uniquement si
                # la borne inf est < au minimum atteint
                $node->greedy_expand; # le parcours se fait bien en profondeur.
            } 
        }
    }
    
    # ---------- end package node --------------------- #
}


my ($nb_tasks, $nb_test) = (8, 20);
my $time;

sub test_exec {
    my ($type) = shift;
    $time = time;
    my ($tot_visit, $min_visit, $max_visit) = (0, 1 << 32, 0);
    foreach my $run (1 .. $nb_test) {
        print "\rRun numero $run";
        ($visited, $global_min, $best_node) = (0, 1 << 32, undef);
        @tasks = tasks_factory($type, $nb_tasks);

        $bsup = calc_time([johnson([0 .. ($nb_tasks - 1)])]);
        my $node = new node([0 .. ($nb_tasks - 1)], [], 0, 0, 0);
        $node->expand;
        $tot_visit += $visited;
        $min_visit = min ($min_visit, $visited);
        $max_visit = max ($max_visit, $visited);
    }
    say "\r" . "-" x 50 . 
        "\nTest ($type) sur $nb_test essaies, instance de taille $nb_tasks :";
    printf "\t- En moyenne : %.f noeuds visités\n", ($tot_visit / $nb_test);
    printf "\t- Minimum de noeuds visités : $min_visit\n" .
        "\t- Maximum de noeuds visités : $max_visit\n";
    printf "\t- Temps moyen : %.2fs\n\n", ((time - $time) / $nb_test);
}

sub verbose_exec {
    $nb_tasks = 14; # CHOISIR LE NOMBRE DE TACHES
    ($visited, $global_min, $binf) = (0, 1 << 32, 1 << 32);
    @tasks = tasks_factory('correl-exec', $nb_tasks); # TYPE D'INSTANCE
    print_tasks();
    
    $bsup = calc_time([johnson([0 .. ($nb_tasks - 1)])]);

    eval {
	# TEST EN GREEDY
	$time = time;
	my $node = new node([0 .. ($nb_tasks - 1)], [], 0, 0, 0);
	$node->greedy_expand;
	$time = time - $time;
	say "GREEDY : ";
	say "Ordonnancement optimal : ";
	say "[ " . (join ", ", map { $_ + 1 } @{$best_node->done}) . " ]";
	say "Temps total de l'ordonnancement optimal : " . $best_node->timeC;
	say "Visités : $visited";
	printf "Temps de traitement : %.2f\n", $time;
    };

    eval {
	# TEST EN NON-GREEDY
	$time = time;
	($visited, $global_min, $binf, $best_node) = (0, 1 << 32, 1 << 32, undef);
	my $node = new node([0 .. ($nb_tasks - 1)], [], 0, 0, 0);
	$node->expand;
	$time = time - $time;
	say "\nNON-GREEDY : ";
	say "Ordonnancement optimal : ";
	say "[ " . (join ", ", map { $_ + 1 } @{$best_node->done}) . " ]";
	say "Temps total de l'ordonnancement optimal : " . $best_node->timeC;
	
	say "Visités : $visited";
	printf "Temps de traitement : %.2f\n", $time;
    };

    
}

verbose_exec();



#say "[" . (join ", ", map { $_ + 1 } (johnson([0 .. ($nb_tasks - 1)]))) . "]";
#say "cout : " . calc_time([johnson([0 .. ($nb_tasks - 1)])]);


#foreach (5, 6, 7, 8, 9, 10, 12, 15, 20) {
#    $nb_tasks = $_;
#   test_exec('correl-exec');
#}


# Fonction de génération d'instance
sub tasks_factory {
    my ($type, $size) = @_;
    my @array_tasks = ([], [], []);

    sswitch ($type) {
        
        case 'non-correl' : {
            foreach (1 .. $size) { # [1;$size]
                my ($atime, $btime, $ctime) = (int(rand(100)+1),
                                               int(rand(100)+1),
                                               int(rand(100)+1));
                push $array_tasks[0], $atime;
                push $array_tasks[1], $btime;
                push $array_tasks[2], $ctime;
            }
            return @array_tasks;   
        }

        case 'correl-exec' : {
            foreach (1 .. $size) {
                my ($r1, $r2, $r3) = (int(rand(5)), int(rand(5)), int(rand(5)));
                push $array_tasks[0], (int(rand(20)) + $r1);
                push $array_tasks[1], (int(rand(20)) + $r2);
                push $array_tasks[2], (int(rand(20)) + $r3);
            }
            return @array_tasks;
        }
        
        case 'exemple' : {
	    $nb_tasks = 8;
            return ([ 35, 12, 25,  6, 76, 56, 54, 25 ], 
                    [ 26, 15, 41, 15, 65, 68, 42, 32 ],
                    [ 13, 19, 21, 25, 51, 42, 28, 31 ]);
        }
        
      default: {
          croak "task_factory : '$type' -> type d'instance inconnnu..";
        }

    }
}

# Affichage du tableau de taches en entrée
sub print_tasks {
    print "Instance testée : \n";
    print "( [ " .  (join ", ", map { /^.$/ ? " $_" : $_ } @{$tasks[0]}) . " ],\n" .
        "  [ " . (join ", ", map { /^.$/ ? " $_" : $_ } @{$tasks[1]}) . " ],\n" .
        "  [ " . (join ", ", map { /^.$/ ? " $_" : $_ } @{$tasks[2]}) . " ] )\n\n";
}


# Traitement du SIGINT
sub handle_int {
    if ($best_node) {
	if ($best_node->timeC != $binf) {
	    say "\n" . "-" x 50;
	    say "Traitement interrompu : APPROXIMATION";
	    printf  "$visited noeuds visités en %.2fs.\n", (time - $time);
	    say "Ordonnancement optimal : ";
	    say "[ " . (join ", ", map { $_ + 1 } @{$best_node->done}) . " ]";
	    say "Temps total de l'ordonnancement optimal : " . $best_node->timeC;
	    say "binf = $binf ; bsup = $bsup";
	    printf "Gap (pas la ville) : %.5f", (($best_node->timeC - $binf)/$binf) * 100; say "%";
	    die;
	}
    } else {
	say "\n" . "-" x 50;
        say "Aucun agencement optimal à afficher.";
    }
}


sub johnson {
    my ($index) = @_;
    my (@g, @d);
    while (@{$index}) {
        my ($min, $cpt, $cpt_min, $i, $j) = (1 << 32, 0);
        foreach my $ind (@{$index}) {
            if ($tasks[0]->[$ind] < $min) {
                $min = $tasks[0]->[$ind];
                $i = $ind; $j = 0; $cpt_min = $cpt ;
            }
            if ($tasks[1]->[$ind] < $min) {
                $min = $tasks[1]->[$ind];
                $i = $ind; $j = 1; $cpt_min = $cpt ;
            }
            $cpt++;
        }
        if ($j == 0) {
            push @g, $i;
        } else {
            unshift @d, $i;
        } 
        splice @{$index}, $cpt_min, 1;
    }
    return (@g, @d);
}

sub calc_time {
    my ($index) = @_;
    my ($ta, $tb, $tc) = (0, 0, 0);
    foreach my $index (@$index) {
        $ta += $tasks[0]->[$index];
        $tb = $tasks[1]->[$index] + ($tb < $ta ? $ta : $tb);
        $tc = $tasks[2]->[$index] + ($tc < $tb ? $tb : $tc);
    }
    return $tc;
}
