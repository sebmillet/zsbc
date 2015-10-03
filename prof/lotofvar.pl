#!/usr/bin/perl -W

use strict;

my $nb_iter = $ARGV[0];
my $nb_vars = 26 * $nb_iter;

my $c;
my $i;

print("\t/* the big() function sets and uses " . $nb_vars . " variables */\n");
print("print \"Part 1: Define the big() function\\n\"\n");
print("define big() {\n");
print("\tprint \"big(): Variables assignment\\n\"\n");

my @all;
my $value = 1;

for (my $c = 0; $c < 26; $c++) {
	my $z = ($c + 10) % 26;
	my $prefix = chr(ord('a') + ($z <= 12 ? $z * 2 : ($z * 2 - 25)));
	$prefix = $prefix . $prefix;

	for (my $i = 0; $i < $nb_iter; $i++) {
		my $postfix = "";
		if ($i % 5 == 0) {
			$postfix = "";
		} elsif ($i % 5 == 1) {
			$postfix = "a";
		} elsif ($i % 5 == 2) {
			$postfix = "z";
		} elsif ($i % 5 == 3) {
			$postfix = "charlie";
		} elsif ($i % 5 == 4) {
			$postfix = "mike";
		}
		my $varname = $prefix . sprintf("%06i", $i) . $postfix;
		push @all, $varname;

		print("\t$varname = $value\n");
		$value++;
	}

}

print("\n\tprint \"big(): Sum calculation\\n\"\n");

my $cc = 0;
for my $elem (@all) {
	if ($cc % 50 == 0) {
		print("\n\tbigadd += $elem");
	} else {
		print("+$elem");
	}
	$cc++;
}
print("\n\treturn bigadd\n");

print("}\n\n");

print("print \"Part 2: Run the big() function\\n\"\n");
print("r=big()\nr\n");

print("print \"Part 3: Check the result\\n\"\n");
print("$nb_vars * ($nb_vars + 1) / 2\n");
print("r - $nb_vars * ($nb_vars + 1) / 2\n\n");
print("quit\n");

