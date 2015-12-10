#!/usr/bin/perl

use strict; use warnings;
no warnings 'deprecated';
no warnings 'recursion';
no warnings 'experimental';
use 5.14.0;
use Switch::Plain;
use sigtrap 'handler' => \&handle_int, 'INT';
use Time::HiRes qw(time);
use Carp;
use List::Util qw(min max);
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
        my ($class, $task, $done, $timeA, $timeB, $timeC, $borne) = @_;
        my $self = {};
        $self->{task} = $task;
        $self->{done} = $done;
        $self->{timeA} = $timeA;
        $self->{timeB} = $timeB;
        $self->{timeC} = $timeC;
        $self->{borne} = $borne;
        $self = bless($self, $class);
        $self->calc_b1_plus; 
        if ($borne eq 'all') {
            $self->calc_b2;
            $self->calc_b3;
        }
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
        return $self->b1 unless exists $self->{b2};
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
        my ($i, $task, $done, $timeA, $timeB, $timeC, $b1, $borne) = 
            (0, $self->{task}, $self->{done}, $self->{timeA}, 
             $self->{timeB}, $self->{timeC}, $self->{b1}, $self->{borne});

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
            my $node = new node (\@task, \@done, $new_timeA, $new_timeB, $new_timeC, $borne);

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
        my ($i, $task, $done, $timeA, $timeB, $timeC, $b1, $borne) = 
            (0, $self->{task}, $self->{done}, $self->{timeA}, 
             $self->{timeB}, $self->{timeC}, $self->{b1}, $self->{borne});

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
            my $node = new node (\@task, \@done, $new_timeA, $new_timeB, $new_timeC, $borne);

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


my ($nb_tasks, $nb_test, $test) = (8, 40, 1);
my $gtime;

sub test_exec {
    my ($type, $intervalle) = @_;
    $gtime = time;
    ($approx, $rapport, $nb_node, $test) = (0, 0.00001, 200_000, 1);

    open my $fp_out, ">results_$type.csv";
    print $fp_out "Nombre de taches;Medianne noeuds visités b1;" . 
        "Medianne noeuds visités max(b1,b2,b3);Medianne noeuds visités b1 (greedy);" .
        "Medianne noeuds visités max(b1,b2,b3) (greedy);" .
        "Temps b1;Temps max(b1,b2,b3);Temps b1 (greedy);Temps max(b1,b2,b3) (greedy);\n";
    close $fp_out;

    foreach my $i (@$intervalle) {
        $nb_tasks = $i;
        print "Test avec $i taches... ";
        my (@arr_median_greed, @arr_median_regular);
        my (@arr_time_greed, @arr_time_regular);
        my %results = ( 'b1_regular' => { 'nb_visited' => 0,
                                          'temps' => 0 },
                        'b1_greedy' => { 'nb_visited' => 0,
                                          'temps' => 0 },
                        'all_regular' => { 'nb_visited' => 0,
                                          'temps' => 0 },
                        'all_greedy' => { 'nb_visited' => 0,
                                          'temps' => 0 }
        );

        foreach my $run (1 .. $nb_test) {
            @tasks = tasks_factory($type, $nb_tasks);
            $bsup = calc_time([johnson([0 .. ($nb_tasks - 1)])]);
            
            foreach my $borne ('b1', 'all') {
                my $time = time;
                eval {
                    ($visited, $global_min, $best_node, $binf) = (0, 1 << 32, undef, 1 << 32);
                    my $node = new node([0 .. ($nb_tasks - 1)], [], 0, 0, 0, $borne);
                    $node->greedy_expand;
                }; 
                $results{"$borne\_greedy"}->{nb_visited} += $visited;
                $results{"$borne\_greedy"}->{temps} += (time - $time);

                $time = time;
                eval {
                    ($visited, $global_min, $best_node, $binf) = (0, 1 << 32, undef, 1 << 32);

                    my $node = new node([0 .. ($nb_tasks - 1)], [], 0, 0, 0, $borne);
                    $node->expand;
                }; 
                $results{"$borne\_regular"}->{nb_visited} += $visited;
                $results{"$borne\_regular"}->{temps} += (time - $time);
            }
            
        }
        # foreach my $borne ('b1', 'all') {
        #     foreach my $algo ('_greedy', '_regular') {
        #         $results{$borne . $algo}->{nb_visited} = 
        #             [sort {$a <=> $b} @{$results{$borne . $algo}->{nb_visited}} ];
        #     }            
        # }   ->[int($nb_test/2)]

        open my $fp_out, ">>results_$type.csv";
        print $fp_out "$nb_tasks;" . $results{"b1_regular"}->{nb_visited} .
            ";" . $results{"all_regular"}->{nb_visited} . ";" .
            $results{"b1_greedy"}->{nb_visited} . ";" .
            $results{"all_greedy"}->{nb_visited} . ";" .
            (int($results{"b1_regular"}->{temps} * 1000) / 1000) . ";" . 
            (int($results{"all_regular"}->{temps} * 1000) / 1000) . ";" .
            (int($results{"b1_greedy"}->{temps} * 1000) / 1000) . ";" . 
            (int($results{"all_greedy"}->{temps} * 1000) / 1000) . ";\n";
        close $fp_out;

        print "[Termine]\n";
    }
    
}

sub verbose_exec {
    my ($nb_task, $type) = @_;
    ($visited, $global_min, $binf, $test) = (0, 1 << 32, 1 << 32, 0);
    @tasks = tasks_factory($type, $nb_task);
    #print_tasks();
    print "Taille : $nb_task ";

    $bsup = calc_time([johnson([0 .. ($nb_tasks - 1)])]);
    # eval {
    #     # TEST EN GREEDY
    #     $gtime = time;
    #     my $node = new node([0 .. ($nb_tasks - 1)], [], 0, 0, 0, 'b1');
    #     $node->greedy_expand;
    #     $gtime = time - $gtime;
    #     say "GREEDY : ";
    #     say "Ordonnancement optimal : ";
    #     say "[ " . (join ", ", map { $_ + 1 } @{$best_node->done}) . " ]";
    #     say "Temps total de l'ordonnancement optimal : " . $best_node->timeC;
    #     say "Visités : $visited";
    #     printf "Temps de traitement : %.2f\n", $gtime;
    # };

    eval {
        # TEST EN NON-GREEDY
        $gtime = time;
        ($visited, $global_min, $binf, $best_node) = (0, 1 << 32, 1 << 32, undef);
        my $node = new node([0 .. ($nb_tasks - 1)], [], 0, 0, 0, 'b1');
        $node->expand;
        $gtime = time - $gtime;
        # say "\nNON-GREEDY : ";
        # say "Ordonnancement optimal : ";
        # say "[ " . (join ", ", map { $_ + 1 } @{$best_node->done}) . " ]";
        # say "Temps total de l'ordonnancement optimal : " . $best_node->timeC;
        # say "Visités : $visited";
        # printf "Temps de traitement : %.2f\n", $gtime;
        say "--> Opti trouvé (" . $best_node->timeC . ")";
    }; 
    
}

# foreach my $number (10000, 20000, 50000) {
#     foreach (1 .. 3) {
#         verbose_exec($number, 'correl-exec');
#     }
# }

#test_exec('non-correl', [ 5 .. 15 ]); 
#test_exec('correl-exec', [ 5 .. 15 ]);
#test_exec('correl-machine', [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80]);


#say "[" . (join ", ", map { $_ + 1 } (johnson([0 .. ($nb_tasks - 1)]))) . "]";
#say "cout : " . calc_time([johnson([0 .. ($nb_tasks - 1)])]);


# test de Johnson
# foreach my $taille (1000, 2000, 5000) {
#     foreach (1 .. 30) {
#         @tasks = tasks_factory('correl-machine', $taille);
#         my $time = time;
#         my @tab = johnson([0 .. ($nb_tasks - 1)]);
#         $time = (time - $time);
#         my $time_ = calc_time(\@tab);
#         my $node = new node([0 .. ($nb_tasks - 1)], [], 0, 0, 0, 'b1');
#         printf "%.2fs --> Gap (pas la ville) : %.5f", $time, (($time_ - $node->b)/$node->b) * 100; say "%";
#     }
# }

say "De base, aucun traitement n'est exécuté.";


# Fonction de génération d'instance
sub tasks_factory {
    my ($type, $size) = @_;
    my @array_tasks = ([], [], []);
    $nb_tasks = $size || 0;

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

        case 'correl-machine' : {
            foreach (1 .. $size) {
                push $array_tasks[0], (int(rand(100)) + 1);
                push $array_tasks[1], (int(rand(100)) + 16);
                push $array_tasks[2], (int(rand(100)) + 31);
            }
            return @array_tasks;
        }
        
        case 'exemple' : {
	    $nb_tasks = 8;
            return ([ 35, 12, 25,  6, 76, 56, 54, 25 ], 
                    [ 26, 15, 41, 15, 65, 68, 42, 32 ],
                    [ 13, 19, 21, 25, 51, 42, 28, 31 ]);
        }

      default : {
          croak "task_factory : '$type' -> type d'instance inconnnu..";
        }

    }
}

# Affichage du tableau de taches en entrée
sub print_tasks {
    print "Instance testée : \n";
    print task_as_string();
}

sub task_as_string {
    return "( [ " .  (join ", ", map { /^.$/ ? " $_" : $_ } @{$tasks[0]}) . " ],\n" .
        "  [ " . (join ", ", map { /^.$/ ? " $_" : $_ } @{$tasks[1]}) . " ],\n" .
        "  [ " . (join ", ", map { /^.$/ ? " $_" : $_ } @{$tasks[2]}) . " ] )\n\n";
}


# Traitement du SIGINT
sub handle_int {
    die if $test;
    if ($best_node) {
        #printf $best_node->timeC . "/$binf --> " . "Gap (pas la ville) : %.5f", (($best_node->timeC - $binf)/$binf) * 100; say "%";
        #die;
	if ($best_node->timeC != $binf) {
	    say "\n" . "-" x 50;
	    say "Traitement interrompu : APPROXIMATION";
	    printf  "$visited noeuds visités en %.2fs.\n", (time - $gtime);
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
