#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

struct Student {
    string nim;
    int grade;
    Student(string nim, int grade) : nim(nim), grade(grade) {}
};

struct HashNode {
    vector<Student> students;
};

class HashTable {
private:
    vector<HashNode> table;
public:
    HashTable() : table(TABLE_SIZE) {}

    int hashFunc(string nim) {
        int hash_val = 0;
        for (char c : nim) {
            hash_val += c;
        }
        return hash_val % TABLE_SIZE;
    }

    void insert(string nim, int grade) {
        int index = hashFunc(nim);
        table[index].students.push_back(Student(nim, grade));
    }

    void remove(string nim) {
        int index = hashFunc(nim);
        vector<Student>& students = table[index].students;
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->nim == nim) {
                students.erase(it);
                cout << "Mahasiswa dengan NIM " << nim << " berhasil dihapus." << endl;
                return;
            }
        }
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan." << endl;
    }

    void searchByNIM(string nim) {
        int index = hashFunc(nim);
        vector<Student>& students = table[index].students;
        for (const auto& student : students) {
            if (student.nim == nim) {
                cout << "Mahasiswa dengan NIM " << nim << " ditemukan dengan nilai " << student.grade << endl;
                return;
            }
        }
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan." << endl;
    }

    void searchByGradeRange() {
        cout << "Mahasiswa dengan nilai antara 80 dan 90:" << endl;
        for (const auto& node : table) {
            for (const auto& student : node.students) {
                if (student.grade >= 80 && student.grade <= 90) {
                    cout << "NIM: " << student.nim << ", Nilai: " << student.grade << endl;
                }
            }
        }
    }
};

int main() {
    HashTable studentTable;
    int choice;
    string nim;
    int grade;

    do {
        cout << "\nMenu:\n"
             << "1. Tambah Data Mahasiswa\n"
             << "2. Hapus Data Mahasiswa\n"
             << "3. Cari Data Mahasiswa berdasarkan NIM\n"
             << "4. Cari Data Mahasiswa berdasarkan Rentang Nilai (80 - 90)\n"
             << "5. Keluar\n";
        cout << "Pilih: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Masukkan NIM mahasiswa: ";
                cin >> nim;
                cout << "Masukkan nilai mahasiswa: ";
                cin >> grade;
                studentTable.insert(nim, grade);
                break;
            case 2:
                cout << "Masukkan NIM mahasiswa yang akan dihapus: ";
                cin >> nim;
                studentTable.remove(nim);
                break;
            case 3:
                cout << "Masukkan NIM mahasiswa yang ingin dicari: ";
                cin >> nim;
                studentTable.searchByNIM(nim);
                break;
            case 4:
                studentTable.searchByGradeRange();
                break;
            case 5:
                cout << "Program selesai." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Ulangi." << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}
