#include "../include/Graph.h"
#include "../s21_graph.h"

using namespace s21;


static char **ft_error(char **tab)
{
	unsigned int i; 

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

static char	*ft_word(char const *s, char c, int i)
{
	int		len_of_word;
	char	*word;

	len_of_word = 0;
	while (s[i + len_of_word] && s[i + len_of_word] != c)
		len_of_word++;
	word = (char *)malloc(sizeof(char) * (len_of_word + 1));
	return (word);
}

static char	**ft_needle(char const *s, char c, char **arrayword)
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

size_t count_rows(const std::string &filename)
{
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
	size_t size_0 = 0;
	while (!inf.eof())
	{
		std::string str0;
		str0 = "";
		std::getline(inf, str0);
		if (!str0.empty())
			size_0++;
		while(str0.empty())
		{
			str0 = "";
			std::getline(inf, str0);
			if (inf.eof())
				break;
		}
	}
	inf.close();
	return size_0;
}

Graph Graph::loadGraphFromFile(const std::string &filename) {
    std::ifstream inf;
    size_t size = 0;
    size_t matrix_size = 0;
    size_t i = 0;
	std::string str2;	
	size = count_rows(filename);//
	inf.open(filename, std::ifstream::in);
	str2 = "";
	std::getline(inf, str2);
	char c[str2.length() + 1];
	str2.copy(c, str2.length() + 1);
	c[str2.length()] = '\0';
	if (ft_cntwd(c, ' ') > 1)//проверка на количество значений в первой строке
	{
		std::cout << "std::invalid_argument::what(): size matrix is invalid" << '\n';
		exit(EXIT_FAILURE);
	}
	std:: size_t pos { } ;
	matrix_size = std::stoi(str2, &pos);
	unsigned **array_num = new unsigned*[matrix_size];//выделяем память под строки
	while (matrix_size > i)
	{
		std::string str2;
		str2 = "";
		std::getline(inf, str2);
		if (str2.empty())
			break;
		char c[str2.length() + 1];
		str2.copy(c, str2.length() + 1);
		c[str2.length()] = '\0';
		char **arrayword = nullptr;
		arrayword = ft_split(c, ' ');
		size_t j = 0;
		array_num[i] = new unsigned[ft_cntwd(c, ' ')];
		while (arrayword[j])
		{
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
		if (j != matrix_size) {
			std::cout << "std::invalid_argument::what(): length not equal to matrix width" << '\n';
			clear_matrix(array_num, matrix_size);
			exit(EXIT_FAILURE);	}
		i++;
	}
	if ((size - 1) != i)
	{
	 	std::cout << "std::invalid_argument::what(): the number of rows is not equal to the size of the matrix" << '\n';
	 	clear_matrix(array_num, matrix_size);
	 	exit(0);
	}
	inf.close();
	Graph date(array_num, matrix_size);
	clear_matrix(array_num, matrix_size);
    return date; //check leaks
}
