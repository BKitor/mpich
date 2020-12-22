/*
 * Copyright (C) by Argonne National Laboratory
 *     See COPYRIGHT in top-level directory
 */

#include "mpiimpl.h"

/* -- Begin Profiling Symbol Block for routine MPI_Grequest_complete */
#if defined(HAVE_PRAGMA_WEAK)
#pragma weak MPI_Grequest_complete = PMPI_Grequest_complete
#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#pragma _HP_SECONDARY_DEF PMPI_Grequest_complete  MPI_Grequest_complete
#elif defined(HAVE_PRAGMA_CRI_DUP)
#pragma _CRI duplicate MPI_Grequest_complete as PMPI_Grequest_complete
#elif defined(HAVE_WEAK_ATTRIBUTE)
int MPI_Grequest_complete(MPI_Request request)
    __attribute__ ((weak, alias("PMPI_Grequest_complete")));
#endif
/* -- End Profiling Symbol Block */

/* Define MPICH_MPI_FROM_PMPI if weak symbols are not supported to build
   the MPI routines.  You can use USE_WEAK_SYMBOLS to see if MPICH is
   using weak symbols to implement the MPI routines. */
#ifndef MPICH_MPI_FROM_PMPI
#undef MPI_Grequest_complete
#define MPI_Grequest_complete PMPI_Grequest_complete
#endif

/*@
   MPI_Grequest_complete - Notify MPI that a user-defined request is complete

Input Parameters:
.  request - Generalized request to mark as complete

.N ThreadSafe

.N Fortran

.N Errors
.N MPI_SUCCESS

.seealso: MPI_Grequest_start
@*/
int MPI_Grequest_complete(MPI_Request request)
{
    int mpi_errno = MPI_SUCCESS;
    MPIR_Request *request_ptr;
    MPIR_FUNC_TERSE_STATE_DECL(MPID_STATE_MPI_GREQUEST_COMPLETE);

    MPIR_ERRTEST_INITIALIZED_ORDIE();

    MPID_THREAD_CS_ENTER(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
    MPIR_FUNC_TERSE_ENTER(MPID_STATE_MPI_GREQUEST_COMPLETE);

    /* Validate handle parameters needing to be converted */
#ifdef HAVE_ERROR_CHECKING
    {
        MPID_BEGIN_ERROR_CHECKS;
        {
            MPIR_ERRTEST_REQUEST(request, mpi_errno);
        }
        MPID_END_ERROR_CHECKS;
    }
#endif /* HAVE_ERROR_CHECKING */

    /* Convert MPI object handles to object pointers */
    MPIR_Request_get_ptr(request, request_ptr);

    /* Validate parameters if error checking is enabled */
#ifdef HAVE_ERROR_CHECKING
    {
        MPID_BEGIN_ERROR_CHECKS;
        {
            MPIR_Request_valid_ptr(request_ptr, mpi_errno);
            if (request_ptr && request_ptr->kind != MPIR_REQUEST_KIND__GREQUEST) {
                mpi_errno =
                    MPIR_Err_create_code(MPI_SUCCESS, MPIR_ERR_RECOVERABLE, __func__, __LINE__,
                                         MPI_ERR_ARG, "**notgenreq", 0);
            }
            if (mpi_errno)
                goto fn_fail;
        }
        MPID_END_ERROR_CHECKS;
    }
#endif /* HAVE_ERROR_CHECKING */

    /* ... body of routine ...  */

    mpi_errno = MPIR_Grequest_complete_impl(request_ptr);
    if (mpi_errno) {
        return fn_fail;
    }

    /* ... end of body of routine ... */

  fn_exit:
    MPIR_FUNC_TERSE_EXIT(MPID_STATE_MPI_GREQUEST_COMPLETE);
    MPID_THREAD_CS_EXIT(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
    return mpi_errno;

  fn_fail:
    /* --BEGIN ERROR HANDLING-- */
#ifdef HAVE_ERROR_CHECKING
    {
        mpi_errno =
            MPIR_Err_create_code(mpi_errno, MPIR_ERR_RECOVERABLE, __func__, __LINE__, MPI_ERR_OTHER,
                                 "**mpi_grequest_complete", "**mpi_grequest_complete %R", request);
    }
#endif
    /* --END ERROR HANDLING-- */
    mpi_errno = MPIR_Err_return_comm(NULL, __func__, mpi_errno);
    goto fn_exit;
}
