#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Simple Linked List Node for parked cars
struct Car {
    string plate;
    Car* next;
};

// Queue for waiting cars (fixed size)
struct Queue {
    string cars[5];
    int front = 0, rear = 0;

    bool isEmpty() { return front == rear; }
    bool isFull() { return rear == 5; }

    void enqueue(string plate) {
        if (!isFull()) cars[rear++] = plate;
        else cout << "Waiting queue full!\n";
    }

    string dequeue() {
        if (isEmpty()) return "";
        string plate = cars[front++];
        if (front == rear) front = rear = 0;
        return plate;
    }

    void display() {
        if (isEmpty()) { cout << "Empty\n"; return; }
        for (int i = front; i < rear; i++) cout << cars[i] << " ";
        cout << endl;
    }
};

// Linked list head
Car* head = nullptr;

// Add car to linked list
void addCarToList(string plate) {
    Car* newCar = new Car{ plate, nullptr };
    if (!head) head = newCar;
    else {
        Car* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newCar;
    }
}

// Remove car from linked list
void removeCarFromList(string plate) {
    Car* temp = head;
    Car* prev = nullptr;
    while (temp) {
        if (temp->plate == plate) { 
            if (prev) prev->next = temp->next;
            else head = temp->next;
            delete temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

// Park a car
void parkCar(vector<string>& slots, Queue& queue) {
    string plate;
    cout << "Enter plate number: ";
    cin >> plate;

    for (int i = 0; i < slots.size(); i++) {
        if (slots[i] == "") {
            slots[i] = plate;
            addCarToList(plate);
            cout << "Car parked in slot " << i + 1 << endl;
            return;
        }
    }
    cout << "Parking full! Added to queue.\n";
    queue.enqueue(plate);
}

// Remove a car
void removeCar(vector<string>& slots, Queue& queue) {
    string plate;
    cout << "Enter plate number to remove: ";
    cin >> plate;

    for (int i = 0; i < slots.size(); i++) {
        if (slots[i] == plate) {
            slots[i] = "";
            removeCarFromList(plate);
            cout << "Car removed from slot " << i + 1 << endl;

            string nextCar = queue.dequeue();
            if (nextCar != "") {
                slots[i] = nextCar;
                addCarToList(nextCar);
                cout << "Car from queue parked: " << nextCar << endl;
            }
            return;
        }
    }
    cout << "Car not found.\n";
}

// Display parking slots
void displaySlots(vector<string>& slots) {
    cout << "\nParking Slots:\n";
    for (int i = 0; i < slots.size(); i++)
        cout << "Slot " << i + 1 << ": " << (slots[i] == "" ? "Empty" : slots[i]) << endl;
}

// Display linked list of parked cars
void displayParkedCars() {
    cout << "\nParked Cars: ";
    if (!head) cout << "None";
    Car* temp = head;
    while (temp) {
        cout << temp->plate << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    vector<string> slots(5, ""); // 5 dynamic slots
    Queue queue;
    int choice;

    while (true) {
        cout << "\n1. Park Car\n2. Remove Car\n3. Display Slots\n4. Display Queue\n5. Display Parked Cars\n6. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: parkCar(slots, queue); break;
        case 2: removeCar(slots, queue); break;
        case 3: displaySlots(slots); break;
        case 4: queue.display(); break;
        case 5: displayParkedCars(); break;
        case 6: return 0;
        default: cout << "Invalid choice!\n";
        }
    }
}
