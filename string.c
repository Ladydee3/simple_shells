#include "shell.h"

/**
 * _strlen - Function that returns length of a string
 * @str: A string
 * Return: The length
 */
int _strlen(char *str)
{
	int x = 0;

	if (!str)
		return (0);

	while (*str++)
		x++;
	return (x);
}

/**
 * _strcmp - Function that performs comparison of two strings
 * @str1: first string
 * @str2: second string
 * Return: negative if str1 < str2, positive if str1 > str2,
 * zero if str1 == str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - Function that checks if needle
 * starts with haystack
 * @haystack: the string
 * @needle: the substring
 * Return: Address of next haystack, or NULL if otherwise
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Function that concatenates two strings
 * @dest: the destination
 * @src: the source
 * Return: A pointer to dest
 */
char *_strcat(char *dest, char *src)
{
	char *x = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (x);
}
