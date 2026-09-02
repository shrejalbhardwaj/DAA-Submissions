#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Item
{
    string name;
    double weight;
    double value;
    bool divisible;
    int priority;
    
    double valuePerWeight()
    {
        return value / weight;
    }
};

// Sort by priority and then value/weight
void sortItems(Item items[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (items[j].priority > items[j + 1].priority ||
               (items[j].priority == items[j + 1].priority &&
                items[j].valuePerWeight() < items[j + 1].valuePerWeight()))
            {
                Item temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}

double fractionalKnapsack(Item items[], int n, double capacity)
{
    sortItems(items, n);

    cout << "\nSorted Items:\n";

    cout << left
         << setw(15) << "Item"
         << setw(10) << "Weight"
         << setw(10) << "Value"
         << setw(10) << "Priority"
         << setw(15) << "Value/Weight"
         << setw(15) << "Type" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << left
             << setw(15) << items[i].name
             << setw(10) << items[i].weight
             << setw(10) << items[i].value
             << setw(10) << items[i].priority
             << setw(15) << fixed << setprecision(2)
             << items[i].valuePerWeight()
             << setw(15)
             << (items[i].divisible ? "Divisible" : "Indivisible")
             << endl;
    }

    double totalValue = 0;
    double totalWeight = 0;

    cout << "\nItems selected for transport:\n";

    for (int i = 0; i < n; i++)
    {
        if (capacity <= 0)
            break;

        if (items[i].divisible)
        {
            double takenWeight;

            if (items[i].weight <= capacity)
                takenWeight = items[i].weight;
            else
                takenWeight = capacity;

            double takenValue =
                takenWeight * items[i].valuePerWeight();

            totalWeight += takenWeight;
            totalValue += takenValue;
            capacity -= takenWeight;

            cout << items[i].name
                 << " -> "
                 << takenWeight
                 << " kg, Utility = "
                 << takenValue << endl;
        }
        else
        {
            if (items[i].weight <= capacity)
            {
                totalWeight += items[i].weight;
                totalValue += items[i].value;
                capacity -= items[i].weight;

                cout << items[i].name
                     << " -> "
                     << items[i].weight
                     << " kg, Utility = "
                     << items[i].value << endl;
            }
        }
    }

    cout << "\n===== Final Report =====\n";

    cout << "Total weight carried: "
         << fixed << setprecision(2)
         << totalWeight << " kg\n";

    cout << "Total utility value: "
         << totalValue << " units\n";

    return totalValue;
}

int main()
{
    int n;

    cout << "Enter number of relief items: ";
    cin >> n;

    Item items[100];

    for (int i = 0; i < n; i++)
    {
        cout << "\nItem " << i + 1 << ":\n";

        cout << "Name: ";
        cin >> items[i].name;

        cout << "Weight (kg): ";
        cin >> items[i].weight;

        cout << "Utility Value: ";
        cin >> items[i].value;

        int d;

        cout << "Is it divisible? (1 = Yes, 0 = No): ";
        cin >> d;

        items[i].divisible = (d == 1);

        cout << "Priority (1 = High, 2 = Medium, 3 = Low): ";
        cin >> items[i].priority;
    }

    double capacity;

    cout << "\nEnter maximum weight capacity of boat: ";
    cin >> capacity;

    fractionalKnapsack(items, n, capacity);

    return 0;
}
