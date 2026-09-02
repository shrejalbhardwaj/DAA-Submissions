#include <iostream>
#include <string>
using namespace std;

void merge(string a[], int low, int mid, int high)
{
    string temp[100];
    int i = low;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= high)
    {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= high)
        temp[k++] = a[j++];

    for (i = low, k = 0; i <= high; i++, k++)
        a[i] = temp[k];
}

void mergeSort(string a[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);

        merge(a, low, mid, high);
    }
}

int main()
{
    int n;

    cout << "Enter number of customer orders: ";
    cin >> n;

    string orders[100];

    cout << "Enter timestamps (HH:MM):" << endl;

    for (int i = 0; i < n; i++)
    {
        cin >> orders[i];
    }

    cout << "\nBefore Sorting:" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << orders[i] << " ";
    }

    mergeSort(orders, 0, n - 1);

    cout << "\n\nAfter Sorting:" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << orders[i] << " ";
    }

    cout << endl;

    return 0;
}
