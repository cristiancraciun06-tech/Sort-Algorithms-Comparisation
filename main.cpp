#include <iostream>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <random>
#include <algorithm>
using namespace std;
using namespace chrono;

// ===================== Sorting Algorithms =====================

void bubble_sort(int n, int arr[]) {
    int ok;
    do {
        ok = 0;
        for (int i = 1; i < n; i++) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                ok = 1;
            }
        }
    } while (ok);                           //Compară și interschimbă elementele adiacente
}

void insertion_sort(int n, int arr[]) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }                                      //Construiește lista sortată prin inserarea succesivă a fiecărui element nou
}

void selection_sort(int n, int arr[]) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(arr[i], arr[min_idx]);
    }                                     //Caută repetat valoarea minimă din restul listei și o mută la începutul zonei nesortate
}

void merge_helper(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];
    memcpy(L, arr + left, n1 * sizeof(int));
    memcpy(R, arr + mid + 1, n2 * sizeof(int));
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    delete[] L;
    delete[] R;
}

void merge_sort_rec(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_rec(arr, left, mid);
        merge_sort_rec(arr, mid + 1, right);
        merge_helper(arr, left, mid, right);
    }
}

void merge_sort(int n, int arr[]) {
    if (n > 1) merge_sort_rec(arr, 0, n - 1);             //Algoritm de tip "Divide et Impera" care împarte lista în jumătăți
}

void quick_sort(int n, int arr[]) {
    if (n < 2) return;
    int pivot = arr[n / 2];
    int i, j;
    for (i = 0, j = n - 1; ; i++, j--) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i >= j) break;
        swap(arr[i], arr[j]);
    }
    quick_sort(i, arr);
    quick_sort(n - i, arr + i);
}                                                        //Alege un pivot și partitionează lista astfel încât elementele mai mici să ajungă în stânga acestuia

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(int n, int arr[]) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}                                              //Organizează elementele într-o structură de date de tip morman

void shell_sort(int n, int arr[]) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }                                         //O îmbunătățire a Insertion Sort care compară elemente aflate la distanțe mari
}

void cocktail_sort(int n, int arr[]) {
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;
        
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        --end;
        
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = true;
            }
        }
        ++start;
    }                                                   //O variantă bidirecțională de Bubble Sort care parcurge lista în ambele sensuri
}

void radix_sort(int n, int arr[]) {
    if (n <= 1) return;
    
    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) max_val = arr[i];
    }

    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        int* output = new int[n];
        int count[10] = {0};

        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
        
        delete[] output;                                         //Algoritm de sortare non-comparativ care procesează numerele cifră cu cifră
    }
}
// ===================== Data Generators =====================

mt19937 rng(23); 

void gen_random(int* arr, int n) {
    uniform_int_distribution<int> dist(1, 1000000000);
    for (int i = 0; i < n; i++) arr[i] = dist(rng);
}                                                      //pune numere la intamplare

void gen_sorted(int* arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = i;
}

void gen_reverse(int* arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = n - i;
}

void gen_nearly_sorted(int* arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = i;
    int swaps = max(1, n / 20);
    uniform_int_distribution<int> dist(0, n - 1);
    for (int s = 0; s < swaps; s++) {
        int a = dist(rng), b = dist(rng);
        swap(arr[a], arr[b]);
    }
}                                                     //lista este aproape sortata

void gen_few_unique(int* arr, int n) {
    uniform_int_distribution<int> dist(0, 9);
    for (int i = 0; i < n; i++) arr[i] = dist(rng);
}                                                     //lista e formata doar din cateva numere unice, adica se repeta

// ===================== Verification =====================

bool is_sorted(int* arr, int n) {
    for (int i = 1; i < n; i++)
        if (arr[i] < arr[i - 1]) return false;
    return true;
}                                                    //dupa sortare, verifica daca lista este sortata, daca nu afiseaza o eroare

// ===================== Benchmark =====================

struct Algorithm {
    const char* name;
    void (*func)(int, int*);
    bool quadratic;
};                                                  //'quadratic' este pentru bubble, insertion, selection sort, care sunt O(n^2)

struct Generator {
    const char* name;
    void (*func)(int*, int);
};                          

int main() {
    Algorithm algos[] = {
        {"BubbleSort",    bubble_sort,    true},
        {"InsertionSort", insertion_sort, true},
        {"SelectionSort", selection_sort, true},
        {"CocktailSort",  cocktail_sort,  true},
        {"MergeSort",     merge_sort,     false},
        {"QuickSort",     quick_sort,     false},
        {"HeapSort",      heap_sort,      false},
        {"ShellSort",     shell_sort,     false},
        {"RadixSort",     radix_sort,     false}
    };
    int num_algos = sizeof(algos) / sizeof(algos[0]);

    Generator gens[] = {
        {"Random",       gen_random},
        {"Sorted",       gen_sorted},
        {"Reverse",      gen_reverse},
        {"NearlySorted", gen_nearly_sorted},
        {"FewUnique",    gen_few_unique},
    };
    int num_gens = sizeof(gens) / sizeof(gens[0]);

    int sizes[] = {10, 20, 50, 100, 500, 1000, 5000, 10000,
                   50000, 100000, 500000, 1000000, 10000000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    int max_quadratic = 100000;

    FILE* csv = fopen("results.csv", "w");
    if (!csv) {
        fprintf(stderr, "Could not open results.csv\n");
        return 1;
    }
    fprintf(csv, "Algorithm,DataType,Size,Iterations,AvgTime_ns,ArrayMemory_bytes,ExtraMemory_bytes,TotalMemory_bytes\n");

    printf("=== Sorting Algorithm Benchmark ===\n\n");

    for (int si = 0; si < num_sizes; si++) {
        int n = sizes[si];
        size_t array_mem = (size_t)n * sizeof(int);

        printf("--- n = %d ---\n", n);

        for (int gi = 0; gi < num_gens; gi++) {
            int* source = new int[n];
            gens[gi].func(source, n);

            for (int ai = 0; ai < num_algos; ai++) {
                // Skip O(n^2) algorithms for large inputs
                if (algos[ai].quadratic && n > max_quadratic) {
                    fprintf(csv, "%s,%s,%d,0,SKIPPED,SKIPPED,SKIPPED,SKIPPED\n",
                            algos[ai].name, gens[gi].name, n);
                    fflush(csv);
                    continue;
                }

                // Scale iterations: many for small n, few for large n
                int iters;
                if (algos[ai].quadratic) {
                    if      (n <= 100)   iters = 10000;
                    else if (n <= 1000)  iters = 100;
                    else if (n <= 10000) iters = 10;
                    else                 iters = 1;
                } else {
                    if      (n <= 100)    iters = 10000;
                    else if (n <= 1000)   iters = 1000;
                    else if (n <= 10000)  iters = 100;
                    else if (n <= 100000) iters = 10;
                    else                  iters = 1;
                }

                int* work = new int[n];

                // Timed benchmark
                auto t1 = high_resolution_clock::now();
                for (int it = 0; it < iters; it++) {
                    memcpy(work, source, array_mem);
                    algos[ai].func(n, work);
                }
                auto t2 = high_resolution_clock::now();

                long long total_ns = duration_cast<nanoseconds>(t2 - t1).count();
                long long avg_ns = total_ns / iters;

                // Verify correctness
                if (!is_sorted(work, n)) {
                    printf("  ERROR: %s produced unsorted output on %s data!\n",
                           algos[ai].name, gens[gi].name);
                }

                // Memory calculation
                size_t extra_mem;
                if (strcmp(algos[ai].name, "MergeSort") == 0)
                    extra_mem = array_mem; // O(n) temp arrays
                else if (strcmp(algos[ai].name, "QuickSort") == 0)
                    extra_mem = (size_t)(log2((double)n) * 4 * sizeof(int)); // O(log n) stack
                else
                    extra_mem = 3 * sizeof(int); // O(1) extra

                size_t total_mem = array_mem + extra_mem;

                printf("  %-14s | %-13s | %5d iters | avg %12lld ns | mem %zu bytes\n",
                       algos[ai].name, gens[gi].name, iters, avg_ns, total_mem);

                fprintf(csv, "%s,%s,%d,%d,%lld,%zu,%zu,%zu\n",
                        algos[ai].name, gens[gi].name, n, iters,
                        avg_ns, array_mem, extra_mem, total_mem);
                fflush(csv);

                delete[] work;
            }
            delete[] source;
        }
        printf("\n");
    }

    fclose(csv);
    printf("Done! Results saved to results.csv\n");
    return 0;
}