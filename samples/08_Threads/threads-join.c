#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

// print
void print_vect(int *v, int n)
{
  int i;
  for(i=0; i<n; i++)
  {
    printf("%i", v[i]);
  }
  printf("\n");
}

// swap
void swap(int *i, int *j)
{
  int t;
  t = *i;
  *i = *j;
  *j = t;
}

// reverse
void reverse(int * v, int n)
{
  int i;
  for(i = 0; i < (n/2); i++)
  swap(&v[i], &v[n-1-i]);
}

// permutations
int next_permutation(int *v, int n)
{
  int i, j;
  i = n - 1;
  while ((i > 1) && (v[i] < v[i-1])) i--;
  if (v[i] > v[i-1])
  {
    j = n - 1;
    while (v[j] < v[i-1]) j--;
    swap(&v[j], &v[i-1]);
    reverse(&v[i], n-i);
    return 1;
  }
  return 0;
}

// thread function
void * thread_func(void *arg)
{
  int i;
  int n =*(int *)arg;
  int *v = malloc(sizeof(int)*n);
  for(i=0; i<n; i++) v[i] = i+1;
  print_vect(v,n);
  // Generate Permutation of the elements
  while(next_permutation(v,n) != 0)
  {
    print_vect(v, n);
    sync();
  }
  free(v);
  pthread_exit(arg);
}

// main function
int main(int argc, char ** argv)
{
  // VAriables
  void * ret;
  int result;
  pthread_t thread1, thread2;

  // Create thread one
  int size1 = 4;
  result = pthread_create(&thread1, NULL, thread_func, &size1);
  if(result != 0)
  {
    printf("Error creating thread one!\n");
    return EXIT_FAILURE; // -1
  }

  // Create thread two
  int size2 = 3;
  result = pthread_create(&thread2, NULL, thread_func, &size2);
  if(result != 0)
  {
    printf("Error creating thread two!\n");
    return EXIT_FAILURE; // -1
  }

  // Join thread one
  result = pthread_join(thread1, &ret);
  if(result != 0)
  {
    printf("Error joining thread one!\n");
    return EXIT_FAILURE; // -1
  } else printf("Thread one finished with result: %i\n", *(int *)ret); 

  // Join thread two
  result = pthread_join(thread2, &ret);
  if(result != 0)
  {
    printf("Error joining thread two!\n");
    return EXIT_FAILURE; // -1
  } else printf("Thread two finished with result: %i\n", *(int *)ret);


  printf("Job Done!\n");

  return EXIT_SUCCESS; // 0
}
