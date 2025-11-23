int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Error: please provide at least one positive integer" << std::endl;
		return 1;
	}
	
	PmergeMe test;
	test.sort(ac, av);
	return 0;
}