#include "../include/Graph.h"

using namespace s21;

static char	**ft_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

int	ft_cntwd(char const *s, char c)
{
	int	i;
	int	count_of_word;

	i = 0;
	count_of_word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count_of_word++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count_of_word);
}

char	*ft_word(char const *s, char c, int i)
{
	int		len_of_word;
	char	*word;

	len_of_word = 0;
	while (s[i + len_of_word] && s[i + len_of_word] != c)
		len_of_word++;
	word = (char *)malloc(sizeof(char) * (len_of_word + 1));
	return (word);
}

char	**ft_needle(char const *s, char c, char **arrayword)
{
	int	k;
	int	i;
	int	j;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			arrayword[k] = ft_word(s, c, i);
			if (!(arrayword[k]))
				ft_error(arrayword);
			j = 0;
			while (s[i] && s[i] != c)
				arrayword[k][j++] = s[i++];
			arrayword[k++][j] = '\0';
		}
		else
			i++;
	}
	arrayword[k] = NULL;
	return (arrayword);
}

char	**ft_split(char const *s, char c)
{
	char	**arrayword;
	int		l;

	if (!s)
		return (NULL);
	l = ft_cntwd(s, c);
	arrayword = (char **)malloc(sizeof(char *) * (l + 1));
	if (!arrayword)
		return (NULL);
	return (ft_needle(s, c, arrayword));
}

void clear_matrix(unsigned **array_num, size_t matrix_size)
{
	for (size_t s = 0; s < matrix_size; s++)
		delete[] array_num[s];
	delete[] array_num;
}

Graph Graph::loadGraphFromFile(const std::string &filename) {
	std::ifstream inf;
	inf.open(filename, std::ifstream::in);
	if (!inf.is_open()){
		throw std::runtime_error{"Incorrect file path"};
	}
	if (inf.eof() == true){
		throw std::runtime_error{"Empty file"};
	}
	if (inf.fail() == true) {
		throw std::runtime_error{"Bad data on  file"};
	}
	size_t matrix_size = 0;
	while (!inf.eof())
	{
		std::string str0;
		str0 = "";
		std::getline(inf, str0);
		matrix_size++;
	}
	inf.clear();
	inf.seekg(0);
	unsigned **array_num = new unsigned*[matrix_size];
	int i = 0;
	while (!inf.eof())
	{
		std::string str2;
		str2 = "";
		std::getline(inf, str2);
		int empty_string = 0;
		if (str2.empty())
			empty_string = 1;
		char c[str2.length() + 1];
		str2.copy(c, str2.length() + 1);
		c[str2.length()] = '\0';
		char **arrayword = nullptr;
		arrayword = ft_split(c, ' ');
		size_t j = 0;
		array_num[i] = new unsigned[ft_cntwd(c, ' ')];
		while (arrayword[j])
		{
			std:: size_t pos { } ;
			try {
				array_num[i][j] = std::stoi(arrayword[j], &pos);}
			catch(std::invalid_argument const& ex)
			{
				std::cout << "std::invalid_argument::what(): " << ex.what() << '\n';
				clear_matrix(array_num, matrix_size);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		if (empty_string == 1)	{
			std::cout << "std::invalid_argument::what(): row matrix is empty" << '\n';
			clear_matrix(array_num, matrix_size);
			exit(EXIT_FAILURE);	}
		if (j != matrix_size) {
			std::cout << "std::invalid_argument::what(): length not equal to matrix width" << '\n';
			clear_matrix(array_num, matrix_size);
			exit(EXIT_FAILURE);	}
		i++;
	}
	inf.close();
    return Graph(array_num, matrix_size); //check leaks
}
