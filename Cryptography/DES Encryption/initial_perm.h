#ifndef _INITIAL_PERM_H
#define _INITIAL_PERM_H

/*
 * plaintext - The 64 bits that need to be encrypted.
 * 
 * Return: A string containing 64 bits, permuted accordingly.
 */
char* init_perm(char* plaintext);