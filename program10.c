#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fcfs(int requests[], int size, int head);
void sstf(int requests[], int size, int head);
void scan(int requests[], int size, int head);
void cscan(int requests[], int size, int head);
void look(int requests[], int size, int head);
void clook(int requests[], int size, int head);
void sort(int arr[], int n);
int absolute(int x);

int main()
{
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    int size = sizeof(requests) / sizeof(requests[0]);

    printf("FCFS:\n");
    fcfs(requests, size, head);

    printf("\nSSTF:\n");
    sstf(requests, size, head);

    printf("\nSCAN:\n");
    scan(requests, size, head);

    printf("\nC-SCAN:\n");
    cscan(requests, size, head);

    printf("\nLOOK:\n");
    look(requests, size, head);

    printf("\nC-LOOK:\n");
    clook(requests, size, head);

    return 0;
}

void fcfs(int requests[], int size, int head)
{
    int seekCount = 0;
    int distance, curTrack;

    for (int i = 0; i < size; i++)
    {
        curTrack = requests[i];
        distance = absolute(curTrack - head);
        seekCount += distance;
        head = curTrack;
    }

    printf("Total seek operations: %d\n", seekCount);
}

void sstf(int requests[], int size, int head)
{
    int seekCount = 0;
    int distance, curTrack;
    int *left = (int *)malloc(size * sizeof(int));
    int *right = (int *)malloc(size * sizeof(int));
    int lsize = 0, rsize = 0;

    for (int i = 0; i < size; i++)
    {
        if (requests[i] < head)
            left[lsize++] = requests[i];
        else if (requests[i] > head)
            right[rsize++] = requests[i];
    }

    sort(left, lsize);
    sort(right, rsize);

    while (lsize > 0 || rsize > 0)
    {
        if (lsize > 0 && rsize > 0)
        {
            if (absolute(left[lsize - 1] - head) < absolute(right[0] - head))
            {
                curTrack = left[--lsize];
            }
            else
            {
                curTrack = right[0];
                for (int i = 1; i < rsize; i++)
                    right[i - 1] = right[i];
                rsize--;
            }
        }
        else if (lsize > 0)
        {
            curTrack = left[--lsize];
        }
        else
        {
            curTrack = right[0];
            for (int i = 1; i < rsize; i++)
                right[i - 1] = right[i];
            rsize--;
        }

        distance = absolute(curTrack - head);
        seekCount += distance;
        head = curTrack;
    }

    printf("Total seek operations: %d\n", seekCount);
    free(left);
    free(right);
}

void scan(int requests[], int size, int head)
{
    int seekCount = 0;
    int distance, curTrack;
    int *left = (int *)malloc((size + 1) * sizeof(int));
    int *right = (int *)malloc(size * sizeof(int));
    int lsize = 0, rsize = 0;

    left[lsize++] = 0; // Add start
    for (int i = 0; i < size; i++)
    {
        if (requests[i] < head)
            left[lsize++] = requests[i];
        else
            right[rsize++] = requests[i];
    }

    sort(left, lsize);
    sort(right, rsize);

    for (int i = lsize - 1; i >= 0; i--)
    {
        curTrack = left[i];
        distance = absolute(curTrack - head);
        seekCount += distance;
        head = curTrack;
    }

    for (int i = 0; i < rsize; i++)
    {
        curTrack = right[i];
        distance = absolute(curTrack - head);
        seekCount += distance;
        head = curTrack;
    }

    printf("Total seek operations: %d\n", seekCount);
    free(left);
    free(right);
}

void cscan(int requests[], int size, int head)
{
    int seekCount = 0;
    int distance, curTrack;
    int *left = (int *)malloc((size + 1) * sizeof(int));
    int *right = (int *)malloc((size + 1) * sizeof(int));
    int lsize = 0, rsize = 0;

    left[lsize++] = 0;    // Add start
    right[rsize++] = 199; // Add end

    for (int i = 0; i < size; i++)
    {
        if (requests[i] < head)
            left[lsize++] = requests[i];
        else
            right[rsize++] = requests[i];
    }

    sort(left, lsize);
    sort(right, rsize);

    for (int i = 0; i < rsize; i++)
    {
        curTrack = right[i];
        distance = absolute(curTrack - head);
        seekCount += distance;
        head = curTrack;
    }

    head = 0; // Move head to the start of the disk

    for (int i = 0; i < lsize; i++)
    {
        curTrack = left[i];
        distance = absolute(curTrack - head);
        seekCount += distance;
        head = curTrack;
    }

    printf("Total seek operations: %d\n", seekCount);
    free(left);
    free(right);
}

void look(int requests[], int size, int head)
{
    int seekCount = 0;
    int distance, curTrack;
    int *left = (int *)malloc(size * sizeof(int));
    int *right = (int *)malloc(size * sizeof(int));
    int lsize = 0, rsize = 0;

    for (int i = 0; i < size; i++)
    {
        if (requests[i] < head)
            left[lsize++] = requests[i];
        else
            right[rsize++] = requests[i];
    }

    sort(left, lsize);
    sort(right, rsize);

    for (int i = lsize - 1; i >= 0; i--)
    {
        curTrack = left[i];
        distance = absolute(curTrack - head);
        seekCount += distance;
        head = curTrack;
    }

    for (int i = 0; i < rsize; i++)
    {
        curTrack = right[i];
        distance = absolute(curTrack - head);
        seekCount += distance;
        head = curTrack;
    }

    printf("Total seek operations: %d\n", seekCount);
    free(left);
    free(right);
}

void clook(int requests[], int size, int head)
{
    int seekCount = 0;
    int distance, curTrack;
    int *left = (int *)malloc(size * sizeof(int));
    int *right = (int *)malloc(size * sizeof(int));
    int lsize = 0, rsize = 0;

    for (int i = 0; i < size; i++)
    {
        if (requests[i] < head)
            left[lsize++] = requests[i];
        else
            right[rsize++] = requests[i];
    }

    sort(left, lsize);
    sort(right, rsize);

    for (int i = 0; i < rsize; i++)
    {
        curTrack = right[i];
        distance = absolute(curTrack - head);
        seekCount += distance;
        head = curTrack;
    }

    for (int i = 0; i < lsize; i++)
    {
        curTrack = left[i];
        distance = absolute(curTrack - head);
        seekCount += distance;
        head = curTrack;
    }

    printf("Total seek operations: %d\n", seekCount);
    free(left);
    free(right);
}

void sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int absolute(int x)
{
    return x > 0 ? x : -x;
}
