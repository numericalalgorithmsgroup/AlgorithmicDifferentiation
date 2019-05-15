template<typename ATYPE>
void dgttrf(int n, ATYPE *dl, ATYPE *d, ATYPE *du, ATYPE *du2, int *ipiv, int *info)
{
    /* System generated locals */
    int i__1;
    ATYPE d__1, d__2;

    /* Local variables */
    int i__;
    ATYPE fact, temp;


    /*  -- LAPACK routine (version 3.2) -- */
    /*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
    /*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
    /*     November 2006 */

    /*     .. Scalar Arguments .. */
    /*     .. */
    /*     .. Array Arguments .. */
    /*     .. */

    /*  Purpose */
    /*  ======= */

    /*  DGTTRF computes an LU factorization of a real tridiagonal matrix A */
    /*  using elimination with partial pivoting and row interchanges. */

    /*  The factorization has the form */
    /*     A = L * U */
    /*  where L is a product of permutation and unit lower bidiagonal */
    /*  matrices and U is upper triangular with nonzeros in only the main */
    /*  diagonal and first two superdiagonals. */

    /*  Arguments */
    /*  ========= */

    /*  N       (input) INTEGER */
    /*          The order of the matrix A. */

    /*  DL      (input/output) DOUBLE PRECISION array, dimension (N-1) */
    /*          On entry, DL must contain the (n-1) sub-diagonal elements of */
    /*          A. */

    /*          On exit, DL is overwritten by the (n-1) multipliers that */
    /*          define the matrix L from the LU factorization of A. */

    /*  D       (input/output) DOUBLE PRECISION array, dimension (N) */
    /*          On entry, D must contain the diagonal elements of A. */

    /*          On exit, D is overwritten by the n diagonal elements of the */
    /*          upper triangular matrix U from the LU factorization of A. */

    /*  DU      (input/output) DOUBLE PRECISION array, dimension (N-1) */
    /*          On entry, DU must contain the (n-1) super-diagonal elements */
    /*          of A. */

    /*          On exit, DU is overwritten by the (n-1) elements of the first */
    /*          super-diagonal of U. */

    /*  DU2     (output) DOUBLE PRECISION array, dimension (N-2) */
    /*          On exit, DU2 is overwritten by the (n-2) elements of the */
    /*          second super-diagonal of U. */

    /*  IPIV    (output) INTEGER array, dimension (N) */
    /*          The pivot indices; for 1 <= i <= n, row i of the matrix was */
    /*          interchanged with row IPIV(i).  IPIV(i) will always be either */
    /*          i or i+1; IPIV(i) = i indicates a row interchange was not */
    /*          required. */

    /*  INFO    (output) INTEGER */
    /*          = 0:  successful exit */
    /*          < 0:  if INFO = -k, the k-th argument had an illegal value */
    /*          > 0:  if INFO = k, U(k,k) is exactly zero. The factorization */
    /*                has been completed, but the factor U is exactly */
    /*                singular, and division by zero will occur if it is used */
    /*                to solve a system of equations. */

    /*  ===================================================================== */

    /*     .. Parameters .. */
    /*     .. */
    /*     .. Local Scalars .. */
    /*     .. */
    /*     .. Intrinsic Functions .. */
    /*     .. */
    /*     .. External Subroutines .. */
    /*     .. */
    /*     .. Executable Statements .. */

    /* Parameter adjustments */
    --ipiv;
    --du2;
    --du;
    --d;
    --dl;

    /* Function Body */
    *info = 0;
    if (n < 0) {
        *info = -1;
        return ;
    }

    /*     Quick return if possible */

    if (n == 0) {
        return ;
    }

    /*     Initialize IPIV(i) = i and DU2(I) = 0 */

    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
        ipiv[i__] = i__;
        /* L10: */
    }
    i__1 = n - 2;
    for (i__ = 1; i__ <= i__1; ++i__) {
        du2[i__] = 0.;
        /* L20: */
    }

    i__1 = n - 2;
    for (i__ = 1; i__ <= i__1; ++i__) {
        if ((d__1 = d[i__], abs(d__1)) >= (d__2 = dl[i__], abs(d__2))) {

            /*           No row interchange required, eliminate DL(I) */

            if (d[i__] != 0.) {
                fact = dl[i__] / d[i__];
                dl[i__] = fact;
                d[i__ + 1] -= fact * du[i__];
            }
        } else {

            /*           Interchange rows I and I+1, eliminate DL(I) */

            fact = d[i__] / dl[i__];
            d[i__] = dl[i__];
            dl[i__] = fact;
            temp = du[i__];
            du[i__] = d[i__ + 1];
            d[i__ + 1] = temp - fact * d[i__ + 1];
            du2[i__] = du[i__ + 1];
            du[i__ + 1] = -fact * du[i__ + 1];
            ipiv[i__] = i__ + 1;
        }
        /* L30: */
    }
    if (n > 1) {
        i__ = n - 1;
        if ((d__1 = d[i__], abs(d__1)) >= (d__2 = dl[i__], abs(d__2))) {
            if (d[i__] != 0.) {
                fact = dl[i__] / d[i__];
                dl[i__] = fact;
                d[i__ + 1] -= fact * du[i__];
            }
        } else {
            fact = d[i__] / dl[i__];
            d[i__] = dl[i__];
            dl[i__] = fact;
            temp = du[i__];
            du[i__] = d[i__ + 1];
            d[i__ + 1] = temp - fact * d[i__ + 1];
            ipiv[i__] = i__ + 1;
        }
    }

    /*     Check for a zero on the diagonal of U. */

    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
        if (d[i__] == 0.) {
            *info = i__;
            goto L50;
        }
        /* L40: */
    }
L50:

    return ;

}

template<typename ATYPE>
void dgtts2(int itrans, int n, int nrhs,
            ATYPE *dl, ATYPE *d, ATYPE *du, ATYPE *du2,
            int *ipiv, ATYPE *b, int ldb)
{
    /* System generated locals */
    int b_dim1, b_offset, i__1, i__2;

    /* Local variables */
    int i__, j, ip;
    ATYPE temp;


    /*  -- LAPACK auxiliary routine (version 3.2) -- */
    /*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
    /*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
    /*     November 2006 */

    /*     .. Scalar Arguments .. */
    /*     .. */
    /*     .. Array Arguments .. */
    /*     .. */

    /*  Purpose */
    /*  ======= */

    /*  DGTTS2 solves one of the systems of equations */
    /*     A*X = B  or  A**T*X = B, */
    /*  with a tridiagonal matrix A using the LU factorization computed */
    /*  by DGTTRF. */

    /*  Arguments */
    /*  ========= */

    /*  ITRANS  (input) INTEGER */
    /*          Specifies the form of the system of equations. */
    /*          = 0:  A * X = B  (No transpose) */
    /*          = 1:  A**T* X = B  (Transpose) */
    /*          = 2:  A**T* X = B  (Conjugate transpose = Transpose) */

    /*  N       (input) INTEGER */
    /*          The order of the matrix A. */

    /*  NRHS    (input) INTEGER */
    /*          The number of right hand sides, i.e., the number of columns */
    /*          of the matrix B.  NRHS >= 0. */

    /*  DL      (input) DOUBLE PRECISION array, dimension (N-1) */
    /*          The (n-1) multipliers that define the matrix L from the */
    /*          LU factorization of A. */

    /*  D       (input) DOUBLE PRECISION array, dimension (N) */
    /*          The n diagonal elements of the upper triangular matrix U from */
    /*          the LU factorization of A. */

    /*  DU      (input) DOUBLE PRECISION array, dimension (N-1) */
    /*          The (n-1) elements of the first super-diagonal of U. */

    /*  DU2     (input) DOUBLE PRECISION array, dimension (N-2) */
    /*          The (n-2) elements of the second super-diagonal of U. */

    /*  IPIV    (input) INTEGER array, dimension (N) */
    /*          The pivot indices; for 1 <= i <= n, row i of the matrix was */
    /*          interchanged with row IPIV(i).  IPIV(i) will always be either */
    /*          i or i+1; IPIV(i) = i indicates a row interchange was not */
    /*          required. */

    /*  B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS) */
    /*          On entry, the matrix of right hand side vectors B. */
    /*          On exit, B is overwritten by the solution vectors X. */

    /*  LDB     (input) INTEGER */
    /*          The leading dimension of the array B.  LDB >= max(1,N). */

    /*  ===================================================================== */

    /*     .. Local Scalars .. */
    /*     .. */
    /*     .. Executable Statements .. */

    /*     Quick return if possible */

    /* Parameter adjustments */
    --dl;
    --d;
    --du;
    --du2;
    --ipiv;
    b_dim1 = ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;

    /* Function Body */
    if (n == 0 || nrhs == 0) {
        return ;
    }

    if (itrans == 0) {

        /*        Solve A*X = B using the LU factorization of A, */
        /*        overwriting each right hand side vector with its solution. */

        if (nrhs <= 1) {
            j = 1;
L10:

            /*           Solve L*x = b. */

            i__1 = n - 1;
            for (i__ = 1; i__ <= i__1; ++i__) {
                ip = ipiv[i__];
                temp = b[i__ + 1 - ip + i__ + j * b_dim1] - dl[i__] * b[ip +
                        j * b_dim1];
                b[i__ + j * b_dim1] = b[ip + j * b_dim1];
                b[i__ + 1 + j * b_dim1] = temp;
                /* L20: */
            }

            /*           Solve U*x = b. */

            b[n + j * b_dim1] /= d[n];
            if (n > 1) {
                b[n - 1 + j * b_dim1] = (b[n - 1 + j * b_dim1] - du[n - 1]
                                         * b[n + j * b_dim1]) / d[n - 1];
            }
            for (i__ = n - 2; i__ >= 1; --i__) {
                b[i__ + j * b_dim1] = (b[i__ + j * b_dim1] - du[i__] * b[i__
                                       + 1 + j * b_dim1] - du2[i__] * b[i__ + 2 + j * b_dim1]
                                      ) / d[i__];
                /* L30: */
            }
            if (j < nrhs) {
                ++j;
                goto L10;
            }
        } else {
            i__1 = nrhs;
            for (j = 1; j <= i__1; ++j) {

                /*              Solve L*x = b. */

                i__2 = n - 1;
                for (i__ = 1; i__ <= i__2; ++i__) {
                    if (ipiv[i__] == i__) {
                        b[i__ + 1 + j * b_dim1] -= dl[i__] * b[i__ + j *
                                                               b_dim1];
                    } else {
                        temp = b[i__ + j * b_dim1];
                        b[i__ + j * b_dim1] = b[i__ + 1 + j * b_dim1];
                        b[i__ + 1 + j * b_dim1] = temp - dl[i__] * b[i__ + j *
                                                  b_dim1];
                    }
                    /* L40: */
                }

                /*              Solve U*x = b. */

                b[n + j * b_dim1] /= d[n];
                if (n > 1) {
                    b[n - 1 + j * b_dim1] = (b[n - 1 + j * b_dim1] - du[n
                                             - 1] * b[n + j * b_dim1]) / d[n - 1];
                }
                for (i__ = n - 2; i__ >= 1; --i__) {
                    b[i__ + j * b_dim1] = (b[i__ + j * b_dim1] - du[i__] * b[
                                               i__ + 1 + j * b_dim1] - du2[i__] * b[i__ + 2 + j *
                                                       b_dim1]) / d[i__];
                    /* L50: */
                }
                /* L60: */
            }
        }
    } else {

        /*        Solve A**T * X = B. */

        if (nrhs <= 1) {

            /*           Solve U**T*x = b. */

            j = 1;
L70:
            b[j * b_dim1 + 1] /= d[1];
            if (n > 1) {
                b[j * b_dim1 + 2] = (b[j * b_dim1 + 2] - du[1] * b[j * b_dim1
                                     + 1]) / d[2];
            }
            i__1 = n;
            for (i__ = 3; i__ <= i__1; ++i__) {
                b[i__ + j * b_dim1] = (b[i__ + j * b_dim1] - du[i__ - 1] * b[
                                           i__ - 1 + j * b_dim1] - du2[i__ - 2] * b[i__ - 2 + j *
                                                   b_dim1]) / d[i__];
                /* L80: */
            }

            /*           Solve L**T*x = b. */

            for (i__ = n - 1; i__ >= 1; --i__) {
                ip = ipiv[i__];
                temp = b[i__ + j * b_dim1] - dl[i__] * b[i__ + 1 + j * b_dim1]
                       ;
                b[i__ + j * b_dim1] = b[ip + j * b_dim1];
                b[ip + j * b_dim1] = temp;
                /* L90: */
            }
            if (j < nrhs) {
                ++j;
                goto L70;
            }

        } else {
            i__1 = nrhs;
            for (j = 1; j <= i__1; ++j) {

                /*              Solve U**T*x = b. */

                b[j * b_dim1 + 1] /= d[1];
                if (n > 1) {
                    b[j * b_dim1 + 2] = (b[j * b_dim1 + 2] - du[1] * b[j *
                                         b_dim1 + 1]) / d[2];
                }
                i__2 = n;
                for (i__ = 3; i__ <= i__2; ++i__) {
                    b[i__ + j * b_dim1] = (b[i__ + j * b_dim1] - du[i__ - 1] *
                                           b[i__ - 1 + j * b_dim1] - du2[i__ - 2] * b[i__ -
                                                   2 + j * b_dim1]) / d[i__];
                    /* L100: */
                }
                for (i__ = n - 1; i__ >= 1; --i__) {
                    if (ipiv[i__] == i__) {
                        b[i__ + j * b_dim1] -= dl[i__] * b[i__ + 1 + j *
                                                           b_dim1];
                    } else {
                        temp = b[i__ + 1 + j * b_dim1];
                        b[i__ + 1 + j * b_dim1] = b[i__ + j * b_dim1] - dl[
                                                      i__] * temp;
                        b[i__ + j * b_dim1] = temp;
                    }
                    /* L110: */
                }
                /* L120: */
            }
        }
    }

}


template<typename ATYPE>
void dgttrs(const char *trans, int n, int nrhs,
            ATYPE *dl, ATYPE *d, ATYPE *du, ATYPE *du2,
            int *ipiv, ATYPE *b, int ldb, int *info)
{
    /* System generated locals */
    int b_dim1, b_offset;

    /* Local variables */
    int itrans;
    bool notran;


    /*  -- LAPACK routine (version 3.2) -- */
    /*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
    /*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
    /*     November 2006 */

    /*     .. Scalar Arguments .. */
    /*     .. */
    /*     .. Array Arguments .. */
    /*     .. */

    /*  Purpose */
    /*  ======= */

    /*  DGTTRS solves one of the systems of equations */
    /*     A*X = B  or  A**T*X = B, */
    /*  with a tridiagonal matrix A using the LU factorization computed */
    /*  by DGTTRF. */

    /*  Arguments */
    /*  ========= */

    /*  TRANS   (input) CHARACTER*1 */
    /*          Specifies the form of the system of equations. */
    /*          = 'N':  A * X = B  (No transpose) */
    /*          = 'T':  A**T* X = B  (Transpose) */
    /*          = 'C':  A**T* X = B  (Conjugate transpose = Transpose) */

    /*  N       (input) INTEGER */
    /*          The order of the matrix A. */

    /*  NRHS    (input) INTEGER */
    /*          The number of right hand sides, i.e., the number of columns */
    /*          of the matrix B.  NRHS >= 0. */

    /*  DL      (input) DOUBLE PRECISION array, dimension (N-1) */
    /*          The (n-1) multipliers that define the matrix L from the */
    /*          LU factorization of A. */

    /*  D       (input) DOUBLE PRECISION array, dimension (N) */
    /*          The n diagonal elements of the upper triangular matrix U from */
    /*          the LU factorization of A. */

    /*  DU      (input) DOUBLE PRECISION array, dimension (N-1) */
    /*          The (n-1) elements of the first super-diagonal of U. */

    /*  DU2     (input) DOUBLE PRECISION array, dimension (N-2) */
    /*          The (n-2) elements of the second super-diagonal of U. */

    /*  IPIV    (input) INTEGER array, dimension (N) */
    /*          The pivot indices; for 1 <= i <= n, row i of the matrix was */
    /*          interchanged with row IPIV(i).  IPIV(i) will always be either */
    /*          i or i+1; IPIV(i) = i indicates a row interchange was not */
    /*          required. */

    /*  B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS) */
    /*          On entry, the matrix of right hand side vectors B. */
    /*          On exit, B is overwritten by the solution vectors X. */

    /*  LDB     (input) INTEGER */
    /*          The leading dimension of the array B.  LDB >= max(1,N). */

    /*  INFO    (output) INTEGER */
    /*          = 0:  successful exit */
    /*          < 0:  if INFO = -i, the i-th argument had an illegal value */

    /*  ===================================================================== */

    /*     .. Local Scalars .. */
    /*     .. */
    /*     .. External Functions .. */
    /*     .. */
    /*     .. External Subroutines .. */
    /*     .. */
    /*     .. Intrinsic Functions .. */
    /*     .. */
    /*     .. Executable Statements .. */

    /* Parameter adjustments */
    --dl;
    --d;
    --du;
    --du2;
    --ipiv;
    b_dim1 =ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;

    /* Function Body */
    *info = 0;
    notran = *(unsigned char *)trans == 'N' || *(unsigned char *)trans == 'n';
    if (! notran && ! (*(unsigned char *)trans == 'T' || *(unsigned char *)
                       trans == 't') && ! (*(unsigned char *)trans == 'C' || *(unsigned
                                           char *)trans == 'c')) {
        *info = -1;
    } else if (n < 0) {
        *info = -2;
    } else if (nrhs < 0) {
        *info = -3;
    } else if (( ldb < n) && (ldb<1)) {
        *info = -10;
    }
    if (*info != 0) {
        return ;
    }

    /*     Quick return if possible */

    if (n == 0 || nrhs == 0) {
        return;
    }

    /*     Decode TRANS */

    if (notran) {
        itrans = 0;
    } else {
        itrans = 1;
    }

    /*     Determine the number of right-hand sides to solve at a time. */

    dgtts2(itrans, n, nrhs, &dl[1], &d[1], &du[1], &du2[1], &ipiv[1],
           &b[b_offset], ldb);


}

