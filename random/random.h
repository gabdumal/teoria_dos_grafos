
/**********************************************************************************
 * Arquivo	: random.h                                                            *
 * Criação  : 17/05/2002                                                          *
 * Autor    : Eyder Rios                                                          *
 * Descricao: Definicao de funcoes para geracao de numeros aleatorios.            *
 **********************************************************************************/

#ifndef __random_h__
#define __random_h__

#include "types.h"

void     xrandomize      (CARDINAL seed = 0);
ULONG    xrandom         (ULONG limit);
CARDINAL xrandom_range   (CARDINAL min, CARDINAL max);
CARDINAL xrandom_exclude (CARDINAL excluded, CARDINAL limit);

#endif
