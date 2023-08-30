#ifndef _FINAL_PERM_H
#define _FINAL_PERM_H

/*
 * pre_ciphertext - The 64 bits that have been fed into the 16-round Feistel network and now need to be permuted to yield the final ciphertext.
 * 
 * Return: A string containing 64 bits, permuted accordingly.
 */
char* final_perm(char* pre_ciphertext);