/*
 * =====================================================================================
 *
 *       Filename:  numwrap.c
 *
 *    Description:  Abstraction layer to provide a unique interface to zsbc
 *    				for big numbers calculations, while using libgmp or libc
 *    				behind the scene.
 *
 *        Version:  1.0
 *        Created:  14/06/2015 13:16:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sébastien Millet
 *
 * =====================================================================================
 */

#include "common.h"

void nw_libversions()
{
	out("GMP library version %s\n", gmp_version);
}

