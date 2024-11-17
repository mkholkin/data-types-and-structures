// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
//
// // #include "commands.h"
// #include "include/matrix_operations.h"
// #include "utils/time.h"
//
// static void null_matrix(int** matrix, const int rows, const int cols)
// {
//     for (int i = 0; i < rows; i++)
//         for (int j = 0; j < cols; j++)
//             matrix[i][j] = 0;
// }
//
// int main()
// {
//     const int points[] = {
//         10,
//         50,
//         100,
//         250,
//         500,
//         1000,
//         2500,
//         5000
//     };
//     const int n_points = sizeof(points) / sizeof(points[0]);
//
//     matrix_t m = {0};
//     m.data = matrix_realloc(m.data, points[n_points - 1], points[n_points - 1]);
//     csr_matrix sm = {0};
//
//     matrix_t v = {0};
//     v.ncols = 1;
//     v.data = matrix_realloc(v.data, points[n_points - 1], 1);
//     csr_vector sv = {0};
//
//     for (int i = 0; i < sizeof(points) / sizeof(points[0]); i++)
//     {
//         const int point = points[i];
//
//         char filename[1000] = {0};
//         sprintf(filename, "../data/matrix_%dx%d_performance.txt", point, point);
//         FILE *ftime = fopen(filename, "a");
//
//         sprintf(filename, "../data/matrix_%dx%d_mem.txt", point, point);
//         FILE *fmem = fopen(filename, "a");
//
//         m.nrows = point;
//         m.ncols = point;
//
//         v.nrows = point;
//
//         for (int percent = 0; percent <= 100; percent += 10)
//         {
//             printf("[%d x %d, %d%%]\n", point, point, percent);
//             null_matrix(m.data, m.nrows, m.ncols);
//             null_matrix(v.data, v.nrows, v.ncols);
//
//             matrix_random_fill_percent(&m, percent);
//             matrix_random_fill_percent(&v, percent);
//
//             import_csr_matrix(&m, &sm);
//             import_csr_vector(&v, &sv);
//
//             nsec_t normal = 0;
//             nsec_t spare = 0;
//
//             matrix_t dummy = {0};
//             csr_vector s_dummy = {0};
//
//             for (int i = 0; i < 10; i++)
//             {
//                 nsec_t beg = nanoseconds_now();
//                 multiply(&m, &v, &dummy);
//                 nsec_t end = nanoseconds_now();
//                 normal += end - beg;
//
//                 beg = nanoseconds_now();
//                 spare_mv(&sm, &sv, &s_dummy);
//                 end = nanoseconds_now();
//                 spare += end - beg;
//             }
//
//             normal /= 10;
//             const size_t normal_memory = sizeof(m) + sizeof(m.data[0][0]) * m.ncols * m.nrows + sizeof(v) + sizeof(v.data[0][0]) * v.nrows;
//             spare /= 10;
//             const size_t spare_memory = sizeof(sm) + (sizeof(sm.val[0]) + sizeof(sm.col[0])) * sm.nnz + sizeof(sm.row_offset[0]) * (sm.nrows + 1) +
//                 sizeof(sv) + (sizeof(sv.i[0]) + sizeof(sv.val[0])) * sv.nnz;
//
//             printf(
//                 "┌────────────────────────────┬──────────────────────┬────────────────────┐\n"
//                 "│                            │  Time (nanoseconds)  │   Memory (bytes)   │\n"
//                 "├────────────────────────────┼──────────────────────┼────────────────────┤\n"
//                 "│ Common method              │ %19llu  │ %18zu │\n"
//                 "├────────────────────────────┼──────────────────────┼────────────────────┤\n"
//                 "│ Chang & Gustavson          │ %10llu (%+03.2lf%%) │ %8zu (%+03.2lf%%) │\n"
//                 "└────────────────────────────┴──────────────────────┴────────────────────┘\n",
//                 normal, normal_memory,
//                 spare, 100 * ((double)spare - (double)normal) / normal, spare_memory,
//                 100 * ((double) spare_memory - (double) normal_memory) / normal_memory
//             );
//
//             free(dummy.data);
//             free(s_dummy.val);
//
//             printf("\n");
//
//             fprintf(ftime, "%d %+03.2lf%%\n", percent, 100 * ((double)spare - (double)normal) / normal);
//             fprintf(fmem, "%d %+03.2lf%%\n", percent, 100 * ((double) spare_memory - (double) normal_memory) / normal_memory);
//         }
//
//         fclose(ftime);
//         fclose(fmem);
//     }
//
//     free(m.data);
//     free(v.data);
//     free(sm.val);
//     free(sm.col);
//     free(sm.row_offset);
//     free(sv.val);
//     free(sv.i);
// }
