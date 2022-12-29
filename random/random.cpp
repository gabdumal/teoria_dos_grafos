
/**********************************************************************************
 * Arquivo	: random.cpp                                                          *
 * Criação  : 17/05/2002                                                          *
 * Autor    : Eyder Rios                                                          *
 * Descricao: Definicao de funcoes para geracao de numeros aleatorios.            *
 **********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "random.h"


/***********************************************************************************
 * Funcao    : void xrandomize (CARDINAL seed)                                     *
 * Criacao   : 17/04/2002                                                          *
 * Descricao : Inicializa a semente para geracao de numeros  aleatorios. A  funcao *
 *             chama a funcao da biblioteca C srand() passando uma  semente  dife- *
 *             rente a cada chamada.                                               *
 * Parametros: Nenhum                                                              *
 * Retorno   : Nenhum                                                              *
 ***********************************************************************************/

void xrandomize (CARDINAL seed)
{
  if (seed == 0)
    srand ((unsigned) time (NULL));  // a semente e' o no. de segundos desde 1/1/1970
  else
    srand (seed);
}

/***********************************************************************************
 * Funcao    : CARDINAL xrandom (CARDINAL limit)                                   *
 * Criacao   : 17/04/2002                                                          *
 * Descricao : Gera um numero aleatorio entre 0 e limit - 1, inclusive.            *
 * Parametros: limit   - limite superior do numero aleatorio gerado, exclusive.    *
 * Retorno   : Retorna o numero aleatorio gerado.                                  *
 ***********************************************************************************/

ULONG xrandom (ULONG limit)
{
#ifdef __MSDOS__
  return (limit > 0) ? ((ULONG) rand () % limit) : 0;
#else
  return (ULONG) (limit > 0) ? (rand () % limit) : 0;
#endif
}

/***********************************************************************************
 * Funcao    : CARDINAL xrandom_range (CARDINAL min, CARDINAL max)                 *
 * Criacao   : 17/04/2002                                                          *
 * Descricao : Gera um numero aleatorio entre min e max,inclusive. Se  min <= max, *
 *             a funcao retorna min.                                               *
 * Parametros: min     - limite inferior do numero aleatorio gerado, inclusive.    *
 *             max     - limite superior do numero aleatorio gerado, inclusive.    *
 * Retorno   : Retorna o numero aleatorio gerado.                                  *
 ***********************************************************************************/

CARDINAL xrandom_range (CARDINAL min, CARDINAL max)
{
  LONG delta;

  delta = max - min;
  if (delta > 0)
    return  min + xrandom (delta + 1);

  return min;
}

/***********************************************************************************
 * Funcao    : CARDINAL xrandom_exclude (CARDINAL excluded, CARDINAL limit)        *
 * Criacao   : 17/04/2002                                                          *
 * Descricao : Gera um numero aleatorio entre 0 e limit - 1,  excluindo  o  numero *
 *             excluded.                                                           *
 * Parametros: excluded - numero que deve ser excluido entre os numeros gerados.   *
 *             limit    - limite superior do numero aleatorio gerado, exclusive.   *
 * Retorno   : Retorna o numero aleatorio gerado.                                  *
 ***********************************************************************************/

CARDINAL xrandom_exclude (CARDINAL excluded, CARDINAL limit)
{
  CARDINAL  rand;

  rand = xrandom (limit);
  if (rand == excluded)
    rand = (xrandom (2) ? rand + 1 : rand - 1) % limit;

  return rand;
}
