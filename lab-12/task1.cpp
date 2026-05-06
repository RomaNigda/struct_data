#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ctime>

using namespace std;

// Structure for the date of book arrival
struct Date {
    int day, month, year;

    Date(int d = 0, int m = 0, int y = 0) : day(d), month(m), year(y) {
    }

    void show() const {
        cout << day << "." << month << "." << year;
    }

    bool operator<(const Date &other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
};

// Book class
class Book {
private:
    string title;
    string author;
    string genre;
    double price;
    int popularity; // number of sales or rating (higher means more popular)
    Date arrivalDate;

public:
    Book(string t, string a, string g, double p, int pop, Date d)
        : title(t), author(a), genre(g), price(p), popularity(pop), arrivalDate(d) {
    }

    // Getters
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getGenre() const { return genre; }
    double getPrice() const { return price; }
    int getPopularity() const { return popularity; }
    Date getArrivalDate() const { return arrivalDate; }

    // Setters (for updates)
    void setPrice(double p) { price = p; }

    // Display book information
    void display() const {
        cout << left << setw(25) << title
                << setw(20) << author
                << setw(15) << genre
                << right << setw(8) << fixed << setprecision(2) << price
                << setw(10) << popularity
                << "     ";
        arrivalDate.show();
        cout << endl;
    }
};

// ==================== FUNCTIONS FOR WORKING WITH BOOKS ====================

// Adding a new book
void addBook(vector<Book> &store) {
    string title, author, genre;
    double price;
    int popularity, day, month, year;

    cout << "Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Author: ";
    getline(cin, author);
    cout << "Genre: ";
    getline(cin, genre);
    cout << "Price: ";
    cin >> price;
    cout << "Popularity (sales): ";
    cin >> popularity;
    cout << "Arrival date (day month year): ";
    cin >> day >> month >> year;

    store.push_back(Book(title, author, genre, price, popularity, Date(day, month, year)));
    cout << "Book added!\n";
}

// Removing a book by title
void removeBook(vector<Book> &store, const string &title) {
    auto it = remove_if(store.begin(), store.end(),
                        [&title](const Book &b) { return b.getTitle() == title; });

    if (it != store.end()) {
        store.erase(it, store.end());
        cout << "Book \"" << title << "\" removed (sold out).\n";
    } else {
        cout << "Book not found.\n";
    }
}

// Sorting by price (ascending)
void sortByPrice(vector<Book> &store) {
    sort(store.begin(), store.end(),
         [](const Book &a, const Book &b) { return a.getPrice() < b.getPrice(); });
    cout << "Sorted by price (ascending).\n";
}

// Sorting by popularity (descending)
void sortByPopularity(vector<Book> &store) {
    sort(store.begin(), store.end(),
         [](const Book &a, const Book &b) { return a.getPopularity() > b.getPopularity(); });
    cout << "Sorted by popularity (descending).\n";
}

// Sorting by arrival date (newest first)
void sortByDate(vector<Book> &store) {
    sort(store.begin(), store.end(),
         [](const Book &a, const Book &b) { return b.getArrivalDate() < a.getArrivalDate(); });
    cout << "Sorted by arrival date (newest first).\n";
}

// Filtering by genre
void filterByGenre(const vector<Book> &store, const string &genre) {
    cout << "\nBooks of genre \"" << genre << "\":\n";
    cout << left << setw(25) << "Title"
            << setw(20) << "Author"
            << setw(15) << "Genre"
            << right << setw(8) << "Price"
            << setw(10) << "Popular."
            << "  Date\n";
    cout << string(80, '-') << endl;

    bool found = false;
    for (const auto &book: store) {
        if (book.getGenre() == genre) {
            book.display();
            found = true;
        }
    }
    if (!found) cout << "No books of this genre.\n";
}

// Filtering by price range
void filterByPriceRange(const vector<Book> &store, double minPrice, double maxPrice) {
    cout << "\nBooks in price range [" << minPrice << " - " << maxPrice << "]:\n";
    cout << left << setw(25) << "Title"
            << setw(20) << "Author"
            << setw(15) << "Genre"
            << right << setw(8) << "Price"
            << setw(10) << "Popular."
            << "  Date\n";
    cout << string(80, '-') << endl;

    bool found = false;
    for (const auto &book: store) {
        if (book.getPrice() >= minPrice && book.getPrice() <= maxPrice) {
            book.display();
            found = true;
        }
    }
    if (!found) cout << "No books in this price range.\n";
}

// Searching for a book by title
void searchByTitle(const vector<Book> &store, const string &title) {
    auto it = find_if(store.begin(), store.end(),
                      [&title](const Book &b) { return b.getTitle() == title; });

    if (it != store.end()) {
        cout << "\nBook found:\n";
        cout << left << setw(25) << "Title"
                << setw(20) << "Author"
                << setw(15) << "Genre"
                << right << setw(8) << "Price"
                << setw(10) << "Popular."
                << "  Date\n";
        cout << string(80, '-') << endl;
        it->display();
    } else {
        cout << "Book \"" << title << "\" not found.\n";
    }
}

// Displaying the entire assortment
void showAllBooks(const vector<Book> &store) {
    if (store.empty()) {
        cout << "The assortment is empty.\n";
        return;
    }

    cout << "\n=== FULL ASSORTMENT ===\n";
    cout << left << setw(25) << "Title"
            << setw(20) << "Author"
            << setw(15) << "Genre"
            << right << setw(8) << "Price"
            << setw(10) << "Popular."
            << "  Date\n";
    cout << string(80, '-') << endl;

    for (const auto &book: store) {
        book.display();
    }
    cout << endl;
}

// ==================== MAIN MENU ====================
int lab12_task1() {
    vector<Book> bookstore;

    // Adding test books for demonstration
    bookstore.push_back(Book("Master and Margarita", "Bulgakov", "Novel", 250.0, 120, Date(15, 3, 2022)));
    bookstore.push_back(Book("Fahrenheit 451", "Bradbury", "Dystopian", 180.0, 95, Date(10, 7, 2021)));
    bookstore.push_back(Book("Harry Potter", "Rowling", "Fantasy", 320.0, 250, Date(20, 1, 2023)));
    bookstore.push_back(Book("1984", "Orwell", "Dystopian", 200.0, 210, Date(5, 9, 2020)));

    int choice;
    do {
        cout << "\n========== BOOKSTORE MENU ==========\n";
        cout << "1. Add a book\n";
        cout << "2. Remove a book (sold out)\n";
        cout << "3. Sort by price\n";
        cout << "4. Sort by popularity\n";
        cout << "5. Sort by arrival date\n";
        cout << "6. Filter by genre\n";
        cout << "7. Filter by price range\n";
        cout << "8. Search for a book by title\n";
        cout << "9. Show all books\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(bookstore);
                break;
            case 2: {
                string title;
                cout << "Enter the title of the book to remove: ";
                cin.ignore();
                getline(cin, title);
                removeBook(bookstore, title);
                break;
            }
            case 3:
                sortByPrice(bookstore);
                break;
            case 4:
                sortByPopularity(bookstore);
                break;
            case 5:
                sortByDate(bookstore);
                break;
            case 6: {
                string genre;
                cout << "Enter the genre: ";
                cin.ignore();
                getline(cin, genre);
                filterByGenre(bookstore, genre);
                break;
            }
            case 7: {
                double minP, maxP;
                cout << "Minimum price: ";
                cin >> minP;
                cout << "Maximum price: ";
                cin >> maxP;
                filterByPriceRange(bookstore, minP, maxP);
                break;
            }
            case 8: {
                string title;
                cout << "Enter the title of the book to search: ";
                cin.ignore();
                getline(cin, title);
                searchByTitle(bookstore, title);
                break;
            }
            case 9:
                showAllBooks(bookstore);
                break;
            case 0:
                cout << "Thank you for using the program!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
