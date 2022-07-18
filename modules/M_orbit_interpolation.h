/******* Original Forthan code
module M_orbit_interpolation
use M_dimpar
use M_file
use M_orbit
use M_ics

integer * 4, parameter::maxdgr = 13                   !

type T_orbit_1var         !for one variable
integer * 4 ::ipt        !index in ICS0
integer * 4 ::ipar       !mm already done
real * 8, allocatable::mm(:)    !npar, 6
end type


type T_orbit_pwc                          !for one satellite
logical * 4 ::linited = .false.            !initialization(allocate ONE(:)
	integer * 4 ::nvar = 0                     !number of pwc variables
	type(T_orbit_1var), allocatable::ONE(:)               !nvar
	end type


	type T_orbit_table
	type(T_file) FORB                       !orbit file
	type(T_orbit_header) OH                 !header of the orbit file
	type(T_sat_ics) ICS                     !all satellites in the file have the same ICS
	integer * 4 ncomp                         !number of components of each variable(3 or 6)
	integer * 4 npoint                        !number of records in ORBTAB
	integer * 4 ndgr                          !degree of the interpolation
	integer * 4 iepo_start                    !epoch number of the first in memory

	integer * 4 ipt(maxvar)                   !pointer from input parameter - list to internal one
	real * 8, allocatable::dat(:, : , : )       !dimension order, nsat, nvar, nequ, npoint(nequ = nvar * 6)

	type(T_orbit_pwc), allocatable::PWC(:)
	end type
	!
	integer * 4, save::norbtab = 0
	type(T_orbit_table), save::OT(maxsat)   !index itab

	integer * 4, external::l_orbtab

	contains
	function l_alloc_orbtab(OT)
	logical * 4 l_alloc_orbtab
	integer * 4 ierr
	type(T_orbit_table) OT
	allocate(OT%dat(1:OT % OH%nsat, 1 : OT % OH%nequ, 1 : OT % npoint), stat = ierr)

	l_alloc_orbtab = ierr.eq.0
	return
	end function l_alloc_orbtab


	function l_dealloc_orbtab(OT)
	logical * 4 l_dealloc_orbtab
	integer * 4 ierr
	type(T_orbit_table) OT
	deallocate(OT%dat, stat = ierr)
	deallocate(OT%PWC, stat = ierr)
	l_dealloc_orbtab = ierr.eq.0
	return
	end function l_dealloc_orbtab
	end module
************************************/


/**
 * @M_orbit_interpolation.h
 * @author Jianan Lou
 * @date 2022.7.16
 * @brief  Module M_orbit_interpolation
 *
 *
 * @details
 * @see
 */

#ifndef _M_ORBIT_INTERPOLATION_H_
#define _M_ORBIT_INTERPOLATION_H_

#include"M_dimpar.h"
#include"M_file.h"
#include"M_orbit.h"
#include"M_ics.h"

const int maxdgr = 13; 

typedef struct //for one variable
{
	int ipt;        //index in ICS0
	int ipar;       //mm already done
	double *mm;    //npar, 6
}T_orbit_1var;

typedef struct //for one satellite
{
	bool linited = false;            // initialization(allocate ONE(:)
	int nvar = 0;                    // number of pwc variables
	T_orbit_1var *ONE;               //nvar
}T_orbit_pwc;

typedef struct
{
	T_file FORB;                   //orbit file
	T_orbit_header OH;             //header of the orbit file
	T_sat_ics ICS;                 //all satellites in the file have the same ICS
	int ncomp;                     //number of components of each variable(3 or 6)
	int npoint;                    //number of records in ORBTAB
	int ndgr;                      //degree of the interpolation
	int iepo_start;                //epoch number of the first in memory

	int ipt[maxvar];               //pointer from input parameter - list to internal one
	double ***dat;                 //dimension order, nsat, nvar, nequ, npoint(nequ = nvar * 6)
	T_orbit_pwc *PWC;
}T_orbit_table;

static int norbtab = 0;
static T_orbit_table OT[maxsat]; //index itab
extern int l_orbtab;

#endif //_M_ORBIT_INTERPOLATION_H_