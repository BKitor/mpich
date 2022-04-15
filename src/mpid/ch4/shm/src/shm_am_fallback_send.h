/*
 * Copyright (C) by Argonne National Laboratory
 *     See COPYRIGHT in top-level directory
 */

#ifndef SHM_AM_FALLBACK_SEND_H_INCLUDED
#define SHM_AM_FALLBACK_SEND_H_INCLUDED

MPL_STATIC_INLINE_PREFIX int MPIDI_SHM_mpi_isend(const void *buf,
                                                 MPI_Aint count,
                                                 MPI_Datatype datatype,
                                                 int rank,
                                                 int tag,
                                                 MPIR_Comm * comm, int context_offset,
                                                 MPIDI_av_entry_t * addr, MPIR_Request ** request)
{
    int mpi_errno = MPI_SUCCESS;

    MPID_THREAD_CS_ENTER(VCI, MPIDI_VCI(0).lock);
    mpi_errno = MPIDIG_mpi_isend(buf, count, datatype, rank, tag, comm, context_offset, addr, 0, 0,
                                 request);
    MPID_THREAD_CS_EXIT(VCI, MPIDI_VCI(0).lock);

    return mpi_errno;
}

MPL_STATIC_INLINE_PREFIX int MPIDI_SHM_mpi_issend(const void *buf,
                                                  MPI_Aint count,
                                                  MPI_Datatype datatype,
                                                  int rank,
                                                  int tag,
                                                  MPIR_Comm * comm, int context_offset,
                                                  MPIDI_av_entry_t * addr, MPIR_Request ** request)
{
    int mpi_errno = MPI_SUCCESS;

    MPID_THREAD_CS_ENTER(VCI, MPIDI_VCI(0).lock);
    mpi_errno = MPIDIG_mpi_issend(buf, count, datatype, rank, tag, comm, context_offset, addr, 0, 0,
                                  request);
    MPID_THREAD_CS_EXIT(VCI, MPIDI_VCI(0).lock);

    return mpi_errno;
}

MPL_STATIC_INLINE_PREFIX int MPIDI_SHM_isend_coll(const void *buf, MPI_Aint count,
                                                  MPI_Datatype datatype, int rank, int tag,
                                                  MPIR_Comm * comm, int context_offset,
                                                  MPIDI_av_entry_t * addr, MPIR_Request ** request,
                                                  MPIR_Errflag_t * errflag)
{
    int mpi_errno = MPI_SUCCESS;

    MPID_THREAD_CS_ENTER(VCI, MPIDI_VCI(0).lock);
    mpi_errno = MPIDIG_isend_coll(buf, count, datatype, rank, tag, comm, context_offset, addr,
                                  0, 0, request, errflag);
    MPID_THREAD_CS_EXIT(VCI, MPIDI_VCI(0).lock);

    return mpi_errno;
}

MPL_STATIC_INLINE_PREFIX int MPIDI_SHM_mpi_cancel_send(MPIR_Request * sreq)
{
    return MPIDIG_mpi_cancel_send(sreq);
}

#endif /* SHM_AM_FALLBACK_SEND_H_INCLUDED */
