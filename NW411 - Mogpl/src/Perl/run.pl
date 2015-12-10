#!/usr/bin/perl


# Commands to install all required modules :
# (cpanminus, alias cpanm is a Perl package manager)
#    $ sudo apt-get install cpanminus
#    $ sudo cpanm Switch::Plain
#    $ sudo cpanm Scalar::Util
#    $ sudo cpanm Heap::Simple
#    $ sudo cpanm --force Heap::Simple::XS

use warnings;
use strict;
use 5.18.0;
no warnings 'experimental';
use Data::Dumper;
use Switch::Plain;
use Time::HiRes qw(time);
use Heap::Simple;
use Scalar::Util qw(openhandle);

# just an array and a hash to help.
my @directions = ('nord', 'est', 'sud', 'ouest');
my %directions = (nord  => 0,
                  est   => 1,
                  sud   => 2,
                  ouest => 3);


# Launch the REPL.
repl();



# Fonction qui lance les tests demandés à la question c
# Les instances testées sont stockées dans 'instances_qu_c.txt'
# Les résultats sont stockés dans          'results_qu_c.txt'
# Les temps d'execution sont stockés dans  'times_qu_c.csv'
# Pour ce dernier, il se lit verticalement : les temps d'execution de la taille i sont
#   sur la i-ème colonne
# Les tests sont effectués sur 100 instances de chaque type et non 10.
sub qu_c {
    say "\nTests for question c";
    unlink ('instances_qu_c.txt', 'results_qu_c.txt', 'times_qu_c.csv');
    my @times;
    my $cpt = 0;
    foreach my $size (10, 20, 30, 40, 50) {
        say "Generating mazes. size = $size";
        my @mazes = generate_mazes($size, $size, $size, 100);
        say "  And now, solving them...";
        foreach my $maze (@mazes) {
            print_maze($maze, 'instances_qu_c.txt');
            my $start = time;
            my $graph = maze_to_graph($maze);
            my @answer = solve($graph);
            my $end = int((time - $start)*1000) / 1000;
            $times[$cpt] = [] unless $times[$cpt];
            push $times[$cpt], $end;
            print_result(\@answer, 'results_qu_c.txt');
        }
        $cpt++;
    }
    print_times(\@times, 'times_qu_c.csv');
    say "\nLes instances testées se trouvent dans instances_qu_c.txt, " .
        "les résultats dans results_qu_c.txt, et les temps d'exécution dans times_qu_c.csv\n";
    
}

# Fonction qui lance les tests demandés à la question d
# Les instances testées sont stockées dans 'instances_qu_d.txt'
# Les résultats sont stockés dans          'results_qu_d.txt'
# Les temps d'execution sont stockés dans  'times_qu_d.csv'
# Pour ce dernier, il se lit verticalement : les temps d'execution de la taille i sont
#   sur la i-ème colonne
# Les tests sont effectués sur 100 instances de chaque type et non 10.
sub qu_d {
    say "\nTests for question d";
    unlink ('instances_qu_d.txt', 'results_qu_d.txt', 'times_qu_d.csv');
    my @times;
    my $cpt = 0;
    foreach my $nb_obs (10, 20, 30, 40, 50) {
        say "Generating mazes. nb obstacle = $nb_obs";
        my @mazes = generate_mazes(20, 20, $nb_obs, 100);
        say "  And now, solving them...";
        foreach my $maze (@mazes) {
            print_maze($maze, 'instances_qu_d.txt');
            my $start = time;
            my $graph = maze_to_graph($maze);
            my @answer = solve($graph);
            my $end = int((time - $start)*1000) / 1000;
            $times[$cpt] = [] unless $times[$cpt];
            push $times[$cpt], $end;
            print_result(\@answer, 'results_qu_d.txt');
        }
        $cpt++;
    }
    print_times(\@times, 'times_qu_d.csv');
    say "\nLes instances testées se trouvent dans instances_qu_d.txt, " .
        "les résultats dans results_qu_d.txt, et les temps d'exécution dans times_qu_d.csv\n";
}


# Apply Dijkstra algorithm so find the shortest way between the start and the arrival
# in the instance $graph (the only parameter)
sub solve {
    my $graph = shift;

    # Creating the first node
    my $init = { orient => $graph->{orient},
                 cout   => 0,
                 back   => [],
                 x      => $graph->{x_i},
                 y      => $graph->{y_i} };

    # Initializing the Heap
    my $heap = Heap::Simple->new(order => \&order_nodes);
    $heap->insert($init);

    my $grid = $graph->{graph};
    my ($x_e, $y_e) = ($graph->{x_e}, $graph->{y_e});

    # Iterate while there is still some nodes to visit
    while (my $current = $heap->extract_first) {
	# Get fields of current node
        my ($x, $y, $back, $cout, $orient) = ($current->{x}, $current->{y}, $current->{back},
					      $current->{cout}, $current->{orient});

	# Reach the end
        if ($x == $x_e && $y == $y_e) {
            return ($cout, [@$back, $current]);
        }

	# The node has already been expanded
	next if $grid->{$orient}->[$x][$y] != -1;

	# Update the costs array
	$grid->{$orient}->[$x][$y] = $cout;

	# Expand the node (== get his neighbors)
        my @neighbors = get_neighbors($current, $graph);

	# And push the neighbors in the queue
        foreach my $node (@neighbors) {
	    $heap->insert($node);
	}
    }
    # Can't reach arrival point
    return undef;
}

# This is the 'expand' function
# It returns all nodes that a reachable from current,
# and haven't already been visited
sub get_neighbors {
    my ($current, $graph) = @_;
    my ($x, $y, $back, $cout, $orient) = ($current->{x}, $current->{y}, $current->{back},
                                          $current->{cout}, $current->{orient});
    my $grid = $graph->{graph};
    my @neighbors;

    # first, try to change orientation
    sswitch ($orient) {
        case 'sud'  :
        case 'nord' : {
            foreach my $dir ('est', 'ouest') {
                if ($grid->{$dir}->[$x][$y] == -1) {
                    push @neighbors, new_node($x, $y, [@$back, $current], $cout + 1, $dir);
                }
                if ($grid->{$dir}->[$x][$y] == -1) {
                    push @neighbors, new_node($x, $y, [@$back, $current], $cout + 1, $dir);
                }
            }
        }
        case 'est'  :
        case 'ouest' : {
            foreach my $dir ('nord', 'sud') {
                if ($grid->{$dir}->[$x][$y] == -1) {
                    push @neighbors, new_node($x, $y, [@$back, $current], $cout + 1, $dir);
                }
                if ($grid->{$dir}->[$x][$y] == -1) {
                    push @neighbors, new_node($x, $y, [@$back, $current], $cout + 1, $dir);
                }
            }
        }
    }

    # Then try to go forward
    sswitch ($orient) {
        case 'nord': {
            foreach my $i (1 .. 3) {
                last if $x - $i < 0;
		last if  $grid->{$orient}->[$x - $i][$y] == -2;
                push @neighbors, new_node($x - $i, $y, [@$back, $current], $cout + 1, $orient)
                    if $grid->{$orient}->[$x - $i][$y] == -1;
            }
        }
        case 'sud': {
            foreach my $i (1 .. 3) {
                next if $x + $i >=  $graph->{height};
		last if $grid->{$orient}->[$x + $i][$y] == -2;
                push @neighbors, new_node($x + $i, $y, [@$back, $current], $cout + 1, $orient)
                    if $grid->{$orient}->[$x + $i][$y] == -1;
            }
        }    
        case 'est': { 
            foreach my $i (1 .. 3) {
                next if $y + $i >= $graph->{width};
		last if $grid->{$orient}->[$x][$y + $i] == -2;
                push @neighbors, new_node($x, $y + $i, [@$back, $current], $cout + 1, $orient)
                    if $grid->{$orient}->[$x][$y + $i] == -1;
            }
        }
        case 'ouest': {
            foreach my $i (1 .. 3) {
                next if $y - $i < 0;
		last if $grid->{$orient}->[$x][$y - $i] == -2;
                push @neighbors, new_node($x, $y - $i, [@$back, $current], $cout + 1, $orient)
                    if $grid->{$orient}->[$x][$y - $i] == -1;
            }
        }
    }
    
    return @neighbors;
}

# Create a new node. Since nodes are just hashes, it's just a short cut to create a hash.
sub new_node {
    my ($x, $y, $back, $cout, $orient) = @_;
    return { orient => $orient,
             cout   => $cout,
             back   => $back,
             x      => $x,
             y      => $y };
}


# Back trace function, needed to find the way to led to the arrival
sub back_trace {
    my @answer = @{$_[0]};
    my $result = "";

    my $prev = shift @answer;
    foreach my $elem (@answer) {
        # If the orientation has changed, then we did D or G.
        if ($elem->{orient} ne $prev->{orient}) {
            my $i = $directions{($prev->{orient})};
            if ( $elem->{orient} eq $directions[($i+1) % 4]) {
                $result .= " D";
            } elsif ( $elem->{orient} eq $directions[($i-1) % 4] ) {
                $result .= " G";
            } 
            $prev = $elem;
        } else {
            # Else, we moved forward, we just need to know from how much
            if ($elem->{x} != $prev->{x}) {
                $result .= " a" . abs($elem->{x} - $prev->{x});
            } elsif ($elem->{y} != $prev->{y}) {
                $result .= " a" . abs($elem->{y} - $prev->{y});
            } 
	    $prev = $elem;
        }
    }
    return $result;
}


# Read a maze file
# Return an array of all maze contained in the file
sub read_file {
    my $filename = shift;
    open my $fh, "<$filename" or die $!;

    my @mazes; # all mazes are stored in that array

    while (1) {
        my ($height, $width) = <$fh> =~ m/(\d+) (\d+)/;
        # if height = widht = 0, then we reached the end of the file, time to break.
        last if $height == 0 && $width == 0;
        
        my @maze;
        for (1 .. $height) { # read all lines of the maze
            my $line = <$fh>; chomp $line;
            my @line = split " ", $line;
            die "$filename : corrupted file." unless $#line = $width - 1;
            push @maze, [@line];
        }
        
        my $line = <$fh>; chomp $line; # and read the start/arrival coordonates + orientation
        my ($x_i, $y_i, $x_e, $y_e, $orient) = split ' ', $line;
        die "$filename : corrupted file." unless $x_i && $y_i && $x_e && $y_e && $orient;
        die "$filename : corrupted file." unless $orient ~~ ['nord', 'sud', 'est', 'ouest'];

        # And add the maze to our maze list
        push @mazes, { height   =>   $height,
                       width    =>   $width,
                       maze     =>   \@maze,
                       x_i      =>   $x_i,
                       y_i      =>   $y_i,
                       x_e      =>   $x_e,
                       y_e      =>   $y_e,
                       orient   =>   $orient };
    }
    return @mazes;
}


# Initialization function :
#  Initialize the graph from the maze, and return it.
# The graph is represend by a hash (of 4 elems : sud, est, ouest, nord) of 2d-arrays.
# Each cell contain -1 if the cell can be accessed, and -2 otherwise
sub maze_to_graph {
    my $maze = shift;
    my ($height, $width) = ($maze->{height} - 1, $maze->{width} - 1);
    my $grid = $maze->{maze};
    
    my $graph = { nord  => [],
                  sud   => [],
                  est   => [],
                  ouest => [] };

    # Iterate through the maze..
    for (my $i = 0; $i < $height; $i++) {
        for (my $j = 0; $j < $width; $j++) {
            # if there is an obstacle, we put -2 in the graph cell
            if ($grid->[$i][$j] == 1 || $grid->[$i+1][$j]
                    || $grid->[$i][$j+1] || $grid->[$i+1][$j+1]) {
                $graph->{nord}->[$i][$j]  = -2;
                $graph->{sud}->[$i][$j]   = -2;
                $graph->{est}->[$i][$j]   = -2;
                $graph->{ouest}->[$i][$j] = -2;
            } else { # else we put -1
                $graph->{nord}->[$i][$j]  = -1;
                $graph->{sud}->[$i][$j]   = -1;
                $graph->{est}->[$i][$j]   = -1;
                $graph->{ouest}->[$i][$j] = -1;
            }
        }        
    }
    
    return { graph    =>   $graph,
             height   =>   $maze->{height} - 1,
             width    =>   $maze->{width} - 1,
             x_i      =>   $maze->{x_i} - 1,
             y_i      =>   $maze->{y_i} - 1,
             x_e      =>   $maze->{x_e} - 1,
             y_e      =>   $maze->{y_e} - 1,
             orient   =>   $maze->{orient }};
}

# Print a maze in $filename or on the standart output if filename isn't specified
sub print_maze {
    my ($maze, $filename) = @_;
    my $fh;
    
    if ($filename){ # check if we need to open a file
        if (openhandle($filename)) {
            $fh = $filename
        } else {
            open $fh, ">>$filename" or die $!;
        }
    } else {
        $fh = *STDOUT;
    }
    
    my ($height, $width, $grid, $x_i, $y_i, $x_e, $y_e, $orient) =
	($maze->{height}, $maze->{width}, $maze->{maze}, $maze->{x_i}, $maze->{y_i},
	 $maze->{x_e}, $maze->{y_e}, $maze->{orient});
    
    print $fh "$height $width\n";
    for (my $i = 0; $i < $height; $i++) {
	for (my $j = 0; $j < $width; $j++) {
	    print $fh $grid->[$i][$j] . " ";
	}
	print $fh "\n";	
    }
    print $fh "$x_i $y_i $x_e $y_e $orient\n";
}

# print the result of an execution of our algorithm on $filename if it's specified,
#                                                           or on STDOUT otherwise.
# This is the function that will call back_trace to get the required output
sub print_result {
    my ($result, $filename) = @_;
    my $fh;
    
    if ($filename) { # check if we need to open a file
        if (openhandle($filename)) {
            $fh = $filename
        } else {
            open $fh, ">>$filename" or die $!;
        }
    } else {
        $fh = *STDOUT;
    }

    # Note that if $array is a reference to an array, you access his
    #    elements with $array->[$indice] and not $array[$indice]
    if ($result->[1]) { # A solution was found
        my $solution = back_trace($result->[1]);
        print $fh $result->[0] . " $solution\n";
    } else { # Solution not found
        print $fh "-1\n";
    }
}

# A secondary function, needed for the Heap (since nodes are ordered in a Heap)
sub order_nodes {
    my ($a, $b) = @_;
    return $a->{cout} < $b->{cout};
}

# Generate $nb_instances mazes of size ($width, $height) with $nb_obs on each
sub generate_mazes {
    my ($width, $height, $nb_obs, $nb_instances) = @_;

    my @mazes;
    for (1 .. $nb_instances ) {
    start:
        my @maze;
        # Initializing the maze
        for (my $i = 0; $i < $width; $i++) {
            for (my $j = 0; $j < $height; $j++) {
                $maze[$i][$j] = 0;
            }
        }
        # Generating obstacles
        for (1 .. $nb_obs) {
            my ($i, $j) = (int(rand($width)), int(rand($height)));
            $maze[$i][$j] = 1;
        }
        # Generating start and arrival coordonates
        my ($x_i, $y_i) = (int(rand($width-1)) + 1, int(rand($height-1)) + 1);
        my ($x_e, $y_e) = (int(rand($width-1)) + 1, int(rand($height-1)) + 1);
        my $orient = $directions[int(rand(4))];

        # If start or arrival is blocked by an obstacle
        if ($maze[$x_i-1][$y_i-1] == 1 || $maze[$x_i][$y_i-1] == 1 ||
                $maze[$x_i-1][$y_i] == 1 || $maze[$x_i][$y_i] == 1 ||
                    $maze[$x_e-1][$y_e-1] == 1 || $maze[$x_e][$y_e-1] == 1 ||
                        $maze[$x_e-1][$y_e] == 1 || $maze[$x_e][$y_e] == 1) {
            goto start;
        }

        # Add the maze to our maze list
        push @mazes, { height   =>   $height,
                       width    =>   $width,
                       maze     =>   \@maze, # note that \ is the reference-creation operator
                       x_i      =>   $x_i,
                       y_i      =>   $y_i,
                       x_e      =>   $x_e,
                       y_e      =>   $y_e,
                       orient   =>   $orient };
    }
    return @mazes;
}

# print the times generated by qu_c() or qu_d()
# Note that the output is meant to be read by column and not by line
# (we did it that way because it's slightly easier to generate graph from such files)
sub print_times {
    my ($times, $filename) = @_;

    my $fh;
    if ($filename) { # Check if we need to open a file
        if (openhandle($filename)) {
            $fh = $filename
        } else {
            open $fh, ">>$filename" or die $!;
        }
    } else {
        $fh = *STDOUT;
    }

    # note that scalar(@array) return the number of elements in @array
    # note also that if $array is a reference to an array, you dereference it with
    #   @$array or @{$array}
    for (my $i = 0; $i < scalar(@{$times->[0]}); $i++) {
        for (my $j = 0; $j < scalar(@$times); $j++) {
            print $fh $times->[$j][$i] . ";";
        }
        print $fh "\n";
    }
}

    
# -------------------------------------------------------------------- #
    
# On that part, please read the printed text to understand what does the code.
    
# -------------------------------------------------------------------- #

    
# The 'main' function
sub repl {
    $| = 1; # don't wait for \n to flush stdout
    
    say "\n" . "*" x 50 .
        "\nProjet de MOGPL : La balade du robot\n" . "*" x 50 . "\n\n";

 ask:
    print "Selectionner l'operation souhaitée : \n" .
        "   1 - lancement des tests de la question c\n" .
        "   2 - lancement des tests de la question d\n" .
        "   3 - lancement de l'interface de création d'un labyrinthe personnalisé.\n" .
        "   4 - lancement de l'algorithme sur un fichier donné.\n" .
        "   5 - quitter le programme.\n" .
            "Votre choix : ";
    my $response = <>; chomp $response;
    sswitch ($response) {
        case '1' :
            { qu_c() }
        case '2' :
            { qu_d() }
        case '3' :
            { user_maze() }
        case '4' :
            { exec_from_file() }
        case '5' :
            { exit }
        default :
            { say "choix incorrect. Veuillez selectionner 1, 2, ou 3\n"; goto ask }
    }
    say "\n" . "*" x 50 . "\n";
    goto ask;
}


# This function asks question to create a customize maze.
# (I hope you, reader, speak french)
sub user_maze {
 width:
    print "\nVeuillez selectionner la largeur du labyrinthe: ";
    my $width = <>; chomp $width;
    unless ($width =~ /^\d+$/) {
        say "Erreur, vous n'avez pas entré un nombre entier.";
        goto width;
    }

 height:
    print "\nVeuillez selectionner la hauteur du labyrinthe: ";
    my $height = <>; chomp $height;
    unless ($height =~ /^\d+$/) {
        say "Erreur, vous n'avez pas entré un nombre entier.";
        goto height;
    }

 start:
    print "\nVeuillez entrer les coordonnées de départ x y: ";
    my $coord = <>; chomp $coord;
    unless ($coord =~ /^\d+ \d+$/) {
        say "Erreur, vous n'avez pas entré 2 nombre entier.";
        goto start;
    }
    my ($x_i, $y_i) = $coord =~ /(\d+) (\d+)/;

 arrival:
    print "\nVeuillez entrer les coordonnées d'arrivée x y: ";
    $coord = <>; chomp $coord;
    unless ($coord =~ /^\d+ \d+$/) {
        say "Erreur, vous n'avez pas entré 2 nombre entier.";
        goto arrival;
    }
    my ($x_e, $y_e) = $coord =~ /(\d+) (\d+)/;
    
 orient:
    print "\nVeuillez selectionner l'orientation (nord, sud, est, ouest): ";
    my $orient = <>; chomp $orient;
    unless ($orient ~~ @directions) {
        say "Erreur, vous n'avez pas entré une orientation valide.";
        goto orient;
    }

    
 obstacle:
    print "\nVoulez-vous entrer manuellement les obstacles ? (y/n) ";
    my $obstacle = <>; chomp $obstacle;
    unless ($obstacle eq 'y' || $obstacle eq 'Y' || $obstacle eq 'n' || $obstacle eq 'N') {
        say "Erreur, réponse invalide";
        goto obstacle;
    }

    my $maze;
    if ($obstacle eq 'n' || $obstacle eq 'N') {
    nb_obs:
        print "\nEntrez le nombre d'obstacles : ";
        my $nb_obs = <>; chomp $nb_obs;
        unless ($nb_obs =~ /^\d+$/) {
            say "Erreur, vous n'avez pas entré un nombre entier";
            goto nb_obs;
        }
        
        my @mazes = generate_mazes($width, $height, $nb_obs, 1); # generate a list of 1 maze
        $maze = $mazes[0]; # just keep the 1st (and only) maze
        # And update some informations
        $maze->{x_i} = $x_i;
        $maze->{y_i} = $y_i;
        $maze->{x_e} = $x_e;
        $maze->{y_e} = $y_e;
        $maze->{orient} = $orient;
    } else {
        $maze = generate_maze_user_obs($width, $height, $x_i, $y_i, $x_e, $y_e, $orient);
    }

    say "\nLabyrinthe créé.\n";
    print_maze($maze);

    # Now that the maze has been created, we resolve it.
    my $start = time;
    my $graph = maze_to_graph($maze);
    my @answer = solve($graph);
    my $end = int((time - $start)*1000) / 1000;
    say "\nSolution trouvée en $end sec\n";
    print_result(\@answer);

    print "\n\n";   

}


# This function just asks the user to select the coordonates of the obstacle
# on a maze.
sub generate_maze_user_obs {
    my ($width, $height, $x_i, $y_i, $x_e, $y_e, $orient) = @_;
    
    my @maze;
    # Initializing the maze
    for (my $i = 0; $i < $width; $i++) {
        for (my $j = 0; $j < $height; $j++) {
            $maze[$i][$j] = 0;
        }
    }

    say "Lorsque vous aurez finis de sélectionner des obstacles, entrez -1 pour stopper.";
    my ($response, $cpt) = (1, 1);
    while (1) {
        print "Entrez les coordonnées de l'obstacle numéro $cpt : ";
        $response = <>; chomp $response;
        last if $response eq '-1';
        unless ( $response =~ /^\d+ \d+$/) {
            say "Coordonnées incorrectes."; next;
        }
        my ($i, $j) = $response =~ /^(\d+) (\d+)$/;
        if ( $i >= $width || $i < 0 || $j >= $height || $j < 0) {
            say "Coordonnées invalides."; next;
        }
        $maze[$i][$j] = 1;
        $cpt++;
    }
    
    return { height   =>   $height,
             width    =>   $width,
             maze     =>   \@maze,
             x_i      =>   $x_i,
             y_i      =>   $y_i,
             x_e      =>   $x_e,
             y_e      =>   $y_e,
             orient   =>   $orient };
}

# run the algorithm on all mazes of a file specified by the user
sub exec_from_file {
 filename:
    print "\nVeuillez entrer le nom du fichier: ";
    my $filename = <>; chomp $filename;
    unless (-e $filename) {
        say "Erreur, ce fichier n'existe pas.";
        goto filename;
    }

 tpscalc:
    print "\nVoulez-vous afficher les temps de calcul ? (y/n) ";
    my $tpscalc = <>; chomp $tpscalc;
    unless ($tpscalc eq 'y' || $tpscalc eq 'n') {
        say "Réponse incorrecte.";
        goto tpscalc;
    }
    
 printInst:
    print "\nVoulez-vous afficher les instances testées ? (y/n) ";
    my $printInst = <>; chomp $printInst;
    unless ($printInst eq 'y' || $printInst eq 'n') {
        say "Réponse incorrecte.";
        goto printInst;
    }
    
    my @mazes = read_file($filename);
    foreach my $maze (@mazes) {
        print_maze($maze) if $printInst eq 'y';
        my $start = time;
        my $graph = maze_to_graph($maze);
        my @answer = solve($graph);
        my $end = int((time - $start)*1000) / 1000;
        say "Résolu en $end sec." if $tpscalc eq 'y';
        print_result(\@answer);
    }

    say "\nFichier lu entièrement, l'algorithme a été exécuté sur toutes les instances";
}
