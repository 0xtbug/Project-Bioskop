#include <iostream>
#include <string>
#include <ctime> // waktu
#include <iomanip> // table

using namespace std;

const int MAX_USERS = 20; // Maksimum jumlah pengguna
const int MAX_FILMS = 100; // Maksimum jumlah film

struct User {
    string username;
    string password;
    bool isAdmin;
    int saldo;
    string bookings[100];
    int bookingCount = 0;
};
struct Film {
    string judul;
    string genre;
    string jamTayang;
    string jadwalRilis;
    int durasi;
    int harga;
    char seats[8][16];
    bool seatAvailability[8][16];
};
struct Booking {
    string bookingID;
    string filmTitle;
    string user;
    string seats;
};
void registerUser(User* users, int& userCount) {
    if (userCount >= MAX_USERS) {
        cout << "Kapasitas pengguna maksimum tercapai." << endl;
        return;
    }
    User* newUser = new User();
    cout << "Masukkan username baru: ";
    cin >> newUser->username;
    cout << "Masukkan password baru: ";
    cin >> newUser->password;
    newUser->isAdmin = false;
    newUser->saldo = 0;
    users[userCount] = *newUser;
    userCount++;
    cout << "Pengguna berhasil terdaftar." << endl;
}
bool login(User* users, int userCount, bool& isAdmin, int& currentUserIndex) {
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username && users[i].password == password) {
            isAdmin = users[i].isAdmin;
            currentUserIndex = i;
            return true;
        }
    }
    
    cout << "Username atau password salah." << endl;
    return false;
}
void tampilkanKursiTersedia(const Film& film) {
    cout << "Kursi Tersedia:" << endl;
    cout << "  ";
    for (int j = 1; j <= 16; j++) {
        cout << setw(3) << j;
    }
    cout << endl;
    for (int i = 0; i < 8; i++) {
        cout << static_cast<char>('A' + i) << " ";
        for (int j = 0; j < 16; j++) {
            if (film.seatAvailability[i][j]) {
                cout << setw(3) << film.seats[i][j];
            } else {
                cout << setw(3) << 'X';  // 'X' menandakan kursi telah dipesan
            }
        }
        cout << endl;
    }
}
void tambahFilm(Film* films, int& filmCount) {
    if (filmCount >= MAX_FILMS) {
        cout << "Kapasitas film maksimum tercapai." << endl;
        return;
    }
    
    Film* newFilm = new Film();
    // Menginisialisasi semua kursi sebagai tersedia (belum dipesan)
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 16; j++) {
            newFilm->seats[i][j] = 'O';  // 'O' menandakan kursi tersedia
            newFilm->seatAvailability[i][j] = true;  // Menginisialisasi semua kursi sebagai tersedia
        }
    }
    
    cout << "Masukkan judul film: ";
    cin.ignore();
    getline(cin, newFilm->judul);
    cout << "Masukkan genre film: ";
    getline(cin, newFilm->genre);
    cout << "Masukkan durasi film (dalam menit): ";
    cin >> newFilm->durasi;
    cout << "Masukkan jam tayang film (format HH:MM): ";
    cin >> newFilm->jamTayang;
    // Set harga yang telah ditentukan
    newFilm->harga = 25000;
    films[filmCount] = *newFilm;
    filmCount++;
    
    cout << "Film berhasil ditambahkan." << endl;
}
void tambahFilmComingSoon(Film* films, int& filmCount) {
    if (filmCount >= MAX_FILMS) {
        cout << "Kapasitas film maksimum tercapai." << endl;
        return;
    }
    Film* newFilm = new Film();
    cout << "Masukkan judul film: ";
    cin.ignore();
    getline(cin, newFilm->judul);
    cout << "Masukkan genre film: ";
    getline(cin, newFilm->genre);
    cout << "Masukkan tanggal rilis film (format DD/MM/YYYY): ";
    getline(cin, newFilm->jadwalRilis);
    newFilm->jamTayang = "Coming Soon";
    films[filmCount] = *newFilm;
    filmCount++;
    cout << "Film Coming Soon berhasil ditambahkan." << endl;
}
void hapusFilm(Film* films, int& filmCount) {
    if (filmCount <= 0) {
        cout << "Tidak ada film yang tersedia." << endl;
        return;
    }
    
    cout << "Daftar Film:" << endl;
    for (int i = 0; i < filmCount; i++) {
        cout << "Film " << i + 1 << ":" << endl;
        cout << "Judul: " << films[i].judul << endl;
        cout << "Genre: " << films[i].genre << endl;
        cout << "Durasi: " << films[i].durasi << " menit" << endl;
        cout << endl;
    }
    
    int index;
    cout << "Masukkan nomor film yang ingin dihapus: ";
    cin >> index;
    
    if (index >= 1 && index <= filmCount) {
        for (int i = index - 1; i < filmCount - 1; i++) {
            films[i] = films[i + 1];
        }
        
        filmCount--;
        cout << "Film berhasil dihapus." << endl;
    } else {
        cout << "Nomor film tidak valid." << endl;
    }
}
void updateFilm(Film* films, int filmCount) {
    if (filmCount <= 0) {
        cout << "Tidak ada film yang tersedia." << endl;
        return;
    }
    
    cout << "Daftar Film:" << endl;
    for (int i = 0; i < filmCount; i++) {
        cout << i+1 << ". " << films[i].judul << endl;
    }
    
    int choice;
    cout << "Pilih film yang ingin diperbarui: ";
    cin >> choice;
    
    if (choice < 1 || choice > filmCount) {
        cout << "Pilihan tidak valid." << endl;
        return;
    }
    
    Film* selectedFilm = &films[choice - 1];
    
    cout << "Judul Film: " << selectedFilm->judul << endl;
    cout << "1. Perbarui Genre" << endl;
    cout << "2. Perbarui Durasi" << endl;
    cout << "3. Perbarui Jam Tayang" << endl;
    cout << "4. Kembali" << endl;
    cout << "Pilihan Anda: ";
    
    int option;
    cin >> option;
    
    switch (option) {
        case 1:
            cout << "Masukkan genre baru: ";
            cin.ignore();
            getline(cin, selectedFilm->genre);
            cout << "Genre film berhasil diperbarui." << endl;
            break;
        case 2:
            cout << "Masukkan durasi baru (dalam menit): ";
            cin >> selectedFilm->durasi;
            cout << "Durasi film berhasil diperbarui." << endl;
            break;
        case 3:
            cout << "Masukkan jam tayang baru (format HH:MM): ";
            cin >> selectedFilm->jamTayang;
            cout << "Jam tayang film berhasil diperbarui." << endl;
            break;
        case 4:
            cout << "Kembali ke menu admin." << endl;
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
            break;
    }
}
void updateHarga(Film* films, int filmCount) {
    if (filmCount == 0) {
        cout << "Belum ada film yang ditambahkan." << endl;
        return;
    }
    
    int newHarga;
    cout << "Masukkan harga baru: ";
    cin >> newHarga;
    
    for (int i = 0; i < filmCount; i++) {
        films[i].harga = newHarga;
    }
    
    cout << "Harga untuk semua film berhasil diperbarui." << endl;
}

void tampilkanFilmSedangTayang(Film* films, int filmCount) {
    bool adaFilmTayang = false;
    cout << "============================ Film Yang Sedang Tayang ============================" << endl;
    cout << setw(6) << "No" << setw(15) << "Judul" << setw(10) << "Genre" << endl; // Baris header
    for (int i = 0; i < filmCount; i++) {
        if (films[i].jamTayang != "" && films[i].jamTayang != "Coming Soon") {
            adaFilmTayang = true;
            cout << setw(6) << i + 1; // Nomor film
            cout << setw(15) << films[i].judul; // Judul
            cout << setw(10) << films[i].genre; // Genre
            cout << endl;
        }
    }
    
    if (!adaFilmTayang) {
        cout << "Tidak ada film yang sedang tayang." << endl;
    }
}

void beliTiket(Film* films, int filmCount, User* users, int userCount, int currentUserIndex) {
    tampilkanFilmSedangTayang(films, filmCount);

    int filmChoice;
    cout << "\nPilih film untuk melihat detail: ";
    cin >> filmChoice;
    filmChoice--; // Mengatur indeks
    if (filmChoice < 0 || filmChoice >= filmCount) {
        cout << "Pilihan tidak valid." << endl;
        return;
    }
    Film selectedFilm = films[filmChoice];
    cout << "Judul Film: " << selectedFilm.judul << endl;
    cout << "Genre: " << selectedFilm.genre << endl;
    cout << "Durasi: " << selectedFilm.durasi << " menit" << endl;
    cout << "Jam Tayang: " << selectedFilm.jamTayang << endl;
    cout << "Harga: " << selectedFilm.harga << endl;
    cout << endl;
    tampilkanKursiTersedia(selectedFilm);
    // Periksa apakah pengguna memiliki saldo yang lebih besar atau sama dengan nol
    if (users[currentUserIndex].saldo <= 0) {
        cout << "\nSaldo anda 0, silahkan melakukan topup terlebih dahulu!" << endl;
        return;
    }
    int numSeats;
    cout << "Masukkan jumlah kursi yang ingin dipesan: ";
    cin >> numSeats;
    for (int i = 0; i < numSeats; i++) {
        char row;
        int column;
        cout << "Masukkan kursi " << i + 1 << " (misalnya, A1): ";
        cin >> row >> column;
        row = toupper(row);
        int rowIndex = row - 'A';
        int columnIndex = column - 1;
        if (rowIndex < 0 || rowIndex >= 8 || columnIndex < 0 || columnIndex >= 16) {
            cout << "Kursi tidak valid." << endl;
            return;
        }
        char& seat = selectedFilm.seats[rowIndex][columnIndex];
        bool& seatAvailable = selectedFilm.seatAvailability[rowIndex][columnIndex];
        if (!seatAvailable) {
            cout << "Kursi tidak tersedia." << endl;
            return;
        }
        seat = 'X';  // Memperbarui status kursi menjadi 'X' (dipesan)
        seatAvailable = false;  // Tandai kursi sebagai tidak tersedia
        // Menghasilkan ID pemesanan unik
        string bookingID = "B" + to_string(filmChoice) + "-" + row + to_string(column);
        // Membuat catatan pemesanan baru
        Booking newBooking;
        newBooking.bookingID = bookingID;
        newBooking.filmTitle = selectedFilm.judul;
        newBooking.user = users[currentUserIndex].username; // Perbarui menggunakan nama pengguna
        newBooking.seats = row + to_string(column); // Simpan kursi yang dipesan
        // Tambahkan catatan pemesanan ke riwayat pemesanan pengguna
        users[currentUserIndex].bookings[users[currentUserIndex].bookingCount] = bookingID;
        users[currentUserIndex].bookingCount++;
        // Perbarui status ketersediaan kursi dalam array film
        films[filmChoice].seatAvailability[rowIndex][columnIndex] = false;
    }
    cout << "Konfirmasi pemesanan kursi (Y/N): ";
    char choice;
    cin >> choice;
    if (toupper(choice) != 'Y') {
        cout << "Pemesanan kursi dibatalkan." << endl;
        return;
    }
    // Hitung total harga pemesanan
    int totalPrice = selectedFilm.harga * numSeats;
    // Kurangkan saldo pengguna dengan total harga
    users[currentUserIndex].saldo -= totalPrice;
    if (users[currentUserIndex].saldo < 0) {
        cout << "Saldo tidak mencukupi. Silahkan tambahkan dana ke akun Anda." << endl;
        return;
    }
    cout << "Pemesanan kursi berhasil!" << endl;
    cout << "Total harga: " << totalPrice << endl;
}
void tampilkanBooking(const User* users, int userCount, const Film* films, int filmCount, int currentUserIndex) {
    if (userCount == 0) {
        cout << "Tidak ada pengguna yang terdaftar." << endl;
        return;
    }
    cout << "================= Booking Records =================" << endl;
    const User& currentUser = users[currentUserIndex];
    cout << "Username: " << currentUser.username << endl;
    cout << "Jumlah pemesanan tiket: " << currentUser.bookingCount << endl;
    if (currentUser.bookingCount > 0) {
        cout << "Booking IDs:" << endl;
        for (int j = 0; j < currentUser.bookingCount; j++) {
            const string& bookingID = currentUser.bookings[j];
            cout << "- " << bookingID << endl;
            // Temukan film yang terkait dengan ID pemesanan
            int filmIndex = stoi(bookingID.substr(1, bookingID.find('-') - 1));
            const Film& bookedFilm = films[filmIndex];
            cout << "Judul Film: " << bookedFilm.judul << endl;
            cout << "Genre: " << bookedFilm.genre << endl;
            cout << "Jam: " << bookedFilm.jamTayang << endl;
            cout << "========================" << endl;
        }
    } else {
        cout << "Tidak ditemukan pemesanan untuk pengguna ini." << endl;
    }
    cout << endl;
}
void tampilkanFilmComingSoon(Film* films, int filmCount) {
    
    cout << "=================== Coming Soon Films ===================" << endl;
    cout << setw(6) << "No" << setw(20) << "Title" << setw(15) << "Genre" << setw(15) << "Release Date" << endl; // Header row
    bool foundFilm = false;
    for (int i = 0; i < filmCount; i++) {
        if (films[i].jamTayang == "Coming Soon") {
            cout << setw(6) << i + 1; // Film number
            cout << setw(20) << films[i].judul; // Title
            cout << setw(15) << films[i].genre; // Genre
            cout << setw(15) << films[i].jadwalRilis << endl; // Release Date
           foundFilm = true;
        }
    }
    if (!foundFilm) {
        cout << "Tidak ada film Coming Soon yang tersedia." << endl;
    }
}
void isiSaldo(User* users, int userCount, int currentUserIndex) {
    int choice;
    double amount;
    cout << "===== Pembayaran =====" << endl;
    cout << "Pilih metode pembayaran: " << endl;
    cout << "1. Dana" << endl;
    cout << "2. OVO" << endl;
    cout << "3. GoPay" << endl;
    cout << "4. Bank Transfer" << endl;
    cout << "Pilihan anda: ";
    cin >> choice;
    switch (choice) {
            // Payment process using Dana
        case 1:
            cout << "Masukkan jumlah topup: ";
            cin >> amount;
            users[currentUserIndex].saldo += amount;
            cout << "Saldo berhasil ditambahkan. Saldo saat ini: " << users[currentUserIndex].saldo << endl;
            break;
        case 2:
            // Payment process using OVO
            cout << "Masukkan jumlah topup: ";
            cin >> amount;
            users[currentUserIndex].saldo += amount;
            cout << "Saldo berhasil ditambahkan. Saldo saat ini: " << users[currentUserIndex].saldo << endl;
            break;
        case 3:
            // Payment process using GoPay
            cout << "Masukkan jumlah topup: ";
            cin >> amount;
            users[currentUserIndex].saldo += amount;
            cout << "Saldo berhasil ditambahkan. Saldo saat ini: " << users[currentUserIndex].saldo << endl;
            break;
        case 4:
            // Payment process using bank transfer
            cout << "Masukkan jumlah topup: ";
            cin >> amount;
            users[currentUserIndex].saldo += amount;
            cout << "Saldo berhasil ditambahkan. Saldo saat ini: " << users[currentUserIndex].saldo << endl;
            break;
        default:
            cout << "Pilihan salah!" << endl;
            break;
    }
}
void tampilkanWaktuSekarang() {
    time_t now = time(0);
    struct tm* currentTime = localtime(&now);
    int hour = currentTime->tm_hour;
    int minute = currentTime->tm_min;
    int second = currentTime->tm_sec;
    cout << "Waktu sekarang: " << hour << ":" << minute << ":" << second << endl;
}
void adminMenu() {
    cout << "===== Admin Menu =====" << endl;
    cout << "1. List Daftar film sedang tayang" << endl;
    cout << "2. List Daftar film coming soon" << endl;
    cout << "3. Tambah film" << endl;
    cout << "4. Hapus Film" << endl;
    cout << "5. Update Film" << endl;
    cout << "6. Update Harga Film" << endl;
    cout << "7. Tambah film coming soon" << endl;
    cout << "8. Keluar" << endl;
    cout << "Pilihan anda: ";
}
void adminMode(Film* films, int& filmCount) {
    int adminChoice;
    bool exitAdminMenu = false;
    do {
        adminMenu();
        cin >> adminChoice;
        switch (adminChoice) {
            case 1:
                tampilkanFilmSedangTayang(films, filmCount);
                break;
            case 2:
                tampilkanFilmComingSoon(films, filmCount);
                break;
            case 3:
                tambahFilm(films, filmCount);
                break;
            case 4:
                hapusFilm(films, filmCount);
                break;
            case 5:
                updateFilm(films, filmCount);
                break;
            case 6:
                updateHarga(films, filmCount);
                break;
            case 7:
                tambahFilmComingSoon(films, filmCount);
                break;
            case 8:
                exitAdminMenu = true;
                cout << "Keluar dari menu admin" << endl;
                break;
            default:
                cout << "Pilihan salah!" << endl;
                break;
        }
        cout << endl;
    } while (!exitAdminMenu);
}
void userMenu() {
    cout << "===== User Menu =====" << endl;
    cout << "1. List Daftar film sedang tayang" << endl;
    cout << "2. List Daftar film coming soon" << endl;
    cout << "3. Cek saldo" << endl;
    cout << "4. Isi saldo" << endl;
    cout << "5. Lihat kode tiket" << endl;
    cout << "6. Keluar" << endl;
    cout << "Pilihan anda: ";
}
void userMode(User* users, int userCount, Film* films, int filmCount, int currentUserIndex) {
    int userChoice;
    cout << "Hai " << users[currentUserIndex].username << "!, selamat datang" << endl;
    tampilkanWaktuSekarang();
    do {
        userMenu();
        cin >> userChoice;
        switch (userChoice) {
            case 1:
                // Display now showing films
                beliTiket(films, filmCount, users, userCount, currentUserIndex);
                break;
            case 2:
                // Display coming soon films
                tampilkanFilmComingSoon(films, filmCount);
                break;
            case 3:
                // Check balance
                cout << "Saldo anda: " << users[currentUserIndex].saldo << endl;
                break;
            case 4:
                // Add balance
                isiSaldo(users, userCount, currentUserIndex);
                break;
            case 5:
                // View Booking Records
                tampilkanBooking(users, userCount, films, filmCount, currentUserIndex);
                break;
            case 6:
                cout << "Keluar dari menu pengguna." << endl;
                break;
            default:
                cout << "Pilihan salah!" << endl;
                break;
        }
        cout << endl;
    } while (userChoice != 6);
}
int main() {
    User* users = new User[MAX_USERS];
    Film* films = new Film[MAX_FILMS];
    int userCount = 0;
    int filmCount = 0;
    int choice;
    bool isAdmin = false;
    int currentUserIndex = -1;
    // Tambahkan u/p ke array user
    User* adminUser = new User();
    adminUser->username = "admin";
    adminUser->password = "admin";
    adminUser->isAdmin = true;
    users[userCount] = *adminUser;
    userCount++;
    do {
        cout << "===== Aplikasi Bioskop =====" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilihan Anda: ";
        cin >> choice;
        switch (choice) {
            case 1:
                if (login(users, userCount, isAdmin, currentUserIndex)) {
                    if (isAdmin) {
                        adminMode(films, filmCount);
                    } else {
                        userMode(users, userCount, films, filmCount, currentUserIndex);
                    }
                }
                break;
            case 2:
                registerUser(users, userCount);
                break;
            case 3:
                cout << "Keluar" << endl;
                break;
            default:
                cout << "Pilihan salah!" << endl;
                break;
        }
        cout << endl;
    } while (choice != 3);
    
    delete[] users;
    delete[] films;
    return 0;
}
