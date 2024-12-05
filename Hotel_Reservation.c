#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROOMS 100
#define MAX_CUSTOMERS 100
#define MAX_SERVICES 10

//da

// Makro untuk membersihkan layar
#ifdef _WIN32
    #define CLEAR_SCREEN() system("cls")
#else
    #define CLEAR_SCREEN() system("clear")
#endif

typedef struct {
    int id;
    char username[50];
    char password[50];
} Admin;

typedef struct {
    int roomNumber;
    char type[20];
    int isAvailable; // 1 = Available, 0 = Occupied
} Room;

typedef struct {
    char name[50];
    char phone[20];
    char idNumber[20];
    char roomType[20];
    char tanggalkeluar[20];
    char tanggalmasuk[20];
    int price;
    //bagian uji
    int customers[100];
} Customer;

typedef struct {
    char serviceName[50];
    char contact[20];
} Service;

Admin admins[MAX_CUSTOMERS];
Room rooms[MAX_ROOMS];
Customer customers[MAX_CUSTOMERS];
Service services[MAX_SERVICES];


int adminCount = 0, roomCount = 0, customerCount = 0, serviceCount = 0;

// Function prototypes
void mainMenu();
void adminMenu();
void adminRegistration();
void adminLogin();
void adminProgram();
void dataRoomMenu();
void dataCustomerMenu();
void paymentReportMenu();
void visitReportMenu();
void hotelServicesMenu();


void customerMenu();
void hotelServiceInfoCustomer();
void ratingMenu();
void commentMenu();
void roomDescription();
void selfReservation();
void pause();

//bagian untuk fungsi uji coba



// Main function
int main() {
    mainMenu();
    return 0;
}


// Main menu
//selesai
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 4 perulagan, 5 fungsi
void mainMenu() {
    int choice;
    do {
        CLEAR_SCREEN();
        printf("Selamat datang di hotel Kel 41 EL03\n");
        printf("Silahkan pilih:\n");
        printf("1. Admin\n");
        printf("2. Pelanggan\n");
        printf("0. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            adminMenu();
            break;
        case 2:
            customerMenu();
            break;
        
        case 0:
            printf("Terima kasih telah menggunakan layanan kami!\n");
            exit(0);
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
            pause();
        }
    } while (choice != 0);
}


// Admin menu
//selesai
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 4 perulagan, 5 fungsi
void adminMenu() {
    int choice;
    do {
        system("cls");
        printf("UI ADMIN\n");
        printf("1. Registrasi\n");
        printf("2. Login\n");
        printf("0. Kembali\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            adminRegistration();
            break;
        case 2:
            adminLogin();
            break;
        case 0:
            return;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
            pause();
        }
    } while (choice != 0);
}


// Admin registration
//kurang modul input/output
//terdiri atas modul 2 sintaks dasar, 5 fungsi, 6 array
void adminRegistration() {
    system("cls");
    printf("UI Registrasi\n");
    printf("Silahkan masukan ID: ");
    admins[adminCount].id = adminCount + 1;
    printf("%d\n", admins[adminCount].id);

    printf("Silahkan masukan username baru: ");
    scanf("%s", admins[adminCount].username);

    printf("Silahkan masukan password: ");
    scanf("%s", admins[adminCount].password);

    printf("Selamat telah berhasil, silahkan login.\n");
    adminCount++;
    pause();
}


// Admin login
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 4 perulagan, 5 fungsi, 6 array
void adminLogin() {
    char username[50], password[50];
    int found = 0;

    system("cls");
    printf("UI Login\n");
    printf("Silahkan masukan username: ");
    scanf("%s", username);
    printf("Silahkan masukan password: ");
    scanf("%s", password);

    for (int i = 0; i < adminCount; i++) {
        if (strcmp(admins[i].username, username) == 0) {
            if (strcmp(admins[i].password, password) == 0) {
                found = 1;
                printf("Selamat datang %s\n", admins[i].username);
                pause();
                adminProgram();
                break;
            } else {
                printf("Password salah, silahkan ulangi.\n");
                pause();
                return;
            }
        }
    }
    if (!found) {
        printf("Username salah, silahkan ulangi.\n");
        pause();
    }
}


// Admin program
//selesai
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 4 perulagan, 5 fungsi
void adminProgram() {
    int choice;
    do {
        system("cls");
        printf("UI Program Admin\n");
        printf("1. Data kamar\n");
        printf("2. Data pelanggan\n");
        printf("3. Data laporan pembayaran\n");
        printf("4. Data laporan kunjungan\n");
        printf("5. Data informasi layanan hotel\n");
        printf("0. Kembali\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            dataRoomMenu();
            break;
        case 2:
            dataCustomerMenu();
            break;
        case 3:
            paymentReportMenu();
            break;
        case 4:
            visitReportMenu();
            break;
        case 5:
            hotelServicesMenu();
            break;
        case 0:
            return;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
            pause();
        }
    } while (choice != 0);
}


// Room data menu
//kurang modul input/output
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 4 perulagan, 5 fungsi, 6 array, 8 input/output
void dataRoomMenu() {
    int choice;
    do {
        system("cls");
        printf("=== Data Kamar ===\n");
        for (int i = 0; i < roomCount; i++) {
            printf("Kamar No: %d, Tipe: %s, Status: %s\n", 
                rooms[i].roomNumber, 
                rooms[i].type, 
                rooms[i].isAvailable ? "Kosong" : "Terisi");
        }

        printf("\n1. Tambah Kamar\n");
        printf("2. Hapus Kamar\n");
        printf("3. Update Status Kamar\n");
        printf("0. Kembali\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            if (roomCount >= MAX_ROOMS) {
                printf("Kapasitas kamar penuh!\n");
            } else {
                printf("Masukkan nomor kamar: ");
                scanf("%d", &rooms[roomCount].roomNumber);
                printf("Masukkan tipe kamar (standar/VIP/suite): ");
                scanf("%s", rooms[roomCount].type);
                rooms[roomCount].isAvailable = 1; // Default: kosong
                roomCount++;
                printf("Kamar berhasil ditambahkan!\n");
            }
            pause();
            break;
        }
        case 2: {
            int roomNumber, found = 0;
            printf("Masukkan nomor kamar yang akan dihapus: ");
            scanf("%d", &roomNumber);

            for (int i = 0; i < roomCount; i++) {
                if (rooms[i].roomNumber == roomNumber) {
                    for (int j = i; j < roomCount - 1; j++) {
                        rooms[j] = rooms[j + 1];
                    }
                    roomCount--;
                    found = 1;
                    printf("Kamar berhasil dihapus.\n");
                    break;
                }
            }
            if (!found) {
                printf("Kamar tidak ditemukan.\n");
            }
            pause();
            break;
        }
        case 3: {
            int roomNumber, found = 0;
            printf("Masukkan nomor kamar yang statusnya akan diperbarui: ");
            scanf("%d", &roomNumber);

            for (int i = 0; i < roomCount; i++) {
                if (rooms[i].roomNumber == roomNumber) {
                    rooms[i].isAvailable = !rooms[i].isAvailable;
                    printf("Status kamar berhasil diperbarui.\n");
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("Kamar tidak ditemukan.\n");
            }
            pause();
            break;
        }
        case 0:
            return;
        default:
            printf("Pilihan tidak valid.\n");
            pause();
        }
    } while (choice != 0);
}


// Customer data menu
//kurang modul input/output
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 4 perulagan, 5 fungsi, 6 array, 8 input/output
void dataCustomerMenu() {
    int choice;
    do {
        system("cls");
        printf("=== Data Pelanggan ===\n");
        for (int i = 0; i < customerCount; i++) {
            printf("Pelanggan %d:\n", i + 1);
            printf("Nama Lengkap: %s\n", customers[i].name);
            printf("Nomor Telepon: %s\n", customers[i].phone);
            printf("NIK/Paspor: %s\n", customers[i].idNumber);
            printf("Tipe Kamar: %s\n", customers[i].roomType);
            printf("Harga Kamar: %d\n\n", customers[i].price);
            printf("tanggal masuk (dd/mm/yyyy): %s\n", customers[i].tanggalmasuk);
            printf("tanggal masuk (dd/mm/yyyy): %s\n\n", customers[i].tanggalkeluar);
        }

        printf("\n1. Hapus Pelanggan\n");
        printf("0. Kembali\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            int index;
            printf("Masukkan nomor pelanggan yang akan dihapus: ");
            scanf("%d", &index);
            if (index < 1 || index > customerCount) {
                printf("Pelanggan tidak ditemukan.\n");
            } else {
                for (int i = index - 1; i < customerCount - 1; i++) {
                    customers[i] = customers[i + 1];
                }
                customerCount--;
                printf("Pelanggan berhasil dihapus.\n");
            }
            pause();
            break;
        }
        case 0:
            return;
        default:
            printf("Pilihan tidak valid.\n");
            pause();
        }
    } while (choice != 0);
}


// Payment report menu
//kurang modul input/output
//perlu dirapikan
//terdiri atas modul 2 sintaks dasar, 5 fungsi, 8 input/output
void paymentReportMenu() {
    int choice;
    do {
        system("cls");
        printf("=== Data Pelanggan ===\n");
        for (int i = 0; i < customerCount; i++) {
            printf("Pelanggan %d:\n", i + 1);
            printf("tanggal masuk (dd/mm/yyyy): %s\n", customers[i].tanggalmasuk);
            printf("Tipe Kamar: %s\n", customers[i].roomType);
            printf("Harga Kamar: %d\n", customers[i].price);           
            
        }

        printf("\n1. Hapus Pelanggan\n");
        printf("0. Kembali\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            int index;
            printf("Masukkan nomor pelanggan yang akan dihapus: ");
            scanf("%d", &index);
            if (index < 1 || index > customerCount) {
                printf("Pelanggan tidak ditemukan.\n");
            } else {
                for (int i = index - 1; i < customerCount - 1; i++) {
                    customers[i] = customers[i + 1];
                }
                customerCount--;
                printf("Pelanggan berhasil dihapus.\n");
            }
            pause();
            break;
        }
        case 0:
            return;
        default:
            printf("Pilihan tidak valid.\n");
            pause();
        }
    } while (choice != 0);
}


// Visit report menu
//perlu dikerjakan masih error (ketika dipencet tombol untuk dirun programnya, dia tidak mau membuka programnya)
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 5 fungsi, 6 array
void visitReportMenu() {
    system("cls");
    if (customerCount == 0) {
        printf("Belum ada data pelanggan.\n");
        return;
    }

    printf("\n=== Laporan Kunjungan ===\n");

    // Menyusun laporan berdasarkan tanggal masuk
    char currentDate[11] = "";
    int totalVisitors = 0;

    for (int i = 0; i < customerCount; i++) {
        // Jika tanggal berubah, cetak header baru
        if (strcmp(currentDate, customers[i].tanggalmasuk) != 0) {
            if (strlen(currentDate) > 0) {
                printf("\n"); 
            }
            strcpy(currentDate, customers[i].tanggalmasuk);
            printf("Tanggal %s\n", currentDate);
        }
        printf("- %s\n", customers[i].name); // Tampilkan nama pelanggan
        totalVisitors++;
    }

    printf("\nTotal pengunjung: %d\n", totalVisitors);
    printf("0. Keluar\n");
}


// Hotel services menu bagian ADMIN, untuk melakukan input 
//kurang modul input/output 
//SUDAH TERUHUBUNG Hotel services menu PELANGGAN
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 4 perulagan, 5 fungsi, 6 array, 8 input/output
void hotelServicesMenu() {
    int choice;
    do {
        system("cls");
        printf("=== Informasi Layanan Hotel ===\n");
        for (int i = 0; i < serviceCount; i++) {
            printf("Layanan: %s, Kontak: %s\n", services[i].serviceName, services[i].contact);
        }

        printf("\n1. Tambahkan Layanan\n");
        printf("2. Hapus Layanan\n");
        printf("0. Kembali\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            if (serviceCount >= MAX_SERVICES) {
                printf("Kapasitas layanan penuh!\n");
            } else {
                printf("Masukkan nama layanan: ");
                scanf(" %[^\n]", services[serviceCount].serviceName);
                printf("Masukkan kontak layanan: ");
                scanf("%s", services[serviceCount].contact);
                serviceCount++;
                printf("Layanan berhasil ditambahkan!\n");
            }
            pause();
            break;
        }
        case 2: {
            char serviceName[50];
            int found = 0;
            printf("Masukkan nama layanan yang akan dihapus: ");
            scanf(" %[^\n]", serviceName);

            for (int i = 0; i < serviceCount; i++) {
                if (strcmp(services[i].serviceName, serviceName) == 0) {
                    for (int j = i; j < serviceCount - 1; j++) {
                        services[j] = services[j + 1];
                    }
                    serviceCount--;
                    found = 1;
                    printf("Layanan berhasil dihapus.\n");
                    break;
                }
            }
            if (!found) {
                printf("Layanan tidak ditemukan.\n");
            }
            pause();
            break;
        }
        case 0:
            return;
        default:
            printf("Pilihan tidak valid.\n");
            pause();
        }
    } while (choice != 0);
}


// Fungsi Informasi Layanan Hotel bagian pelanggan
//selesai
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 4 perulagan, 5 fungsi
void hotelServiceInfoCustomer() {
    system("cls"); 
    printf("=== Informasi Layanan Hotel ===\n");
    
    if (serviceCount == 0) {
        printf("Belum ada layanan yang tersedia.\n");
    } else {
        for (int i = 0; i < serviceCount; i++) {
            printf("Layanan: %s, Kontak: %s\n", services[i].serviceName, services[i].contact);
        }
    }

    printf("0. Kembali\n");
    
    getchar();
    getchar(); 
}


// Fungsi Menu Rating
//perlu dikerjakan
//kurang modul input/output
//terdiri atas modul 2 sintaks dasar, 5 fungsi, 6 array, 8 input/output
void ratingMenu() {
    printf("\nRating Pelanggan:\n");
    printf("Pelanggan 1: 10/10\n");
    printf("Pelanggan 2: 8/10\n");
    printf("Pelanggan 3: 6/10\n");
    printf("0. Kembali\n");
    getchar();
    getchar();
}


// Fungsi Menu Komentar
//perlu dikerjakan
//kurang modul input/output
//terdiri atas modul 2 sintaks dasar, 5 fungsi, 6 array, 8 input/output
void commentMenu() {
    printf("\nKomentar Pelanggan:\n");
    printf("Pelanggan 1: Hotel ini bagus sekali!\n");
    printf("Pelanggan 2: Mungkin bisa diperbaiki untuk shower-nya!\n");
    printf("pelanggan n: n\n");
    printf("0. Kembali\n");
    getchar();
    getchar();
}


// Fungsi Deskripsi Kamar
//selesai
//terdiri atas modul 2 sintaks dasar, 5 fungsi
void roomDescription() {
    printf("\nDeskripsi Kamar:\n");
    printf("1. Standar: Kamar luas 6x6 meter dengan kasur untuk 2 orang, harga per malam hanya 500.000.\n");
    printf("2. VIP: Kamar luas10x10 meter dengan fasilitas kamar mandi bathub, harga per malam hanya 1.000.000.\n");
    printf("3. Suite: Kamar luas 12x12 meter dengan pemandangan indah, kamar mandi bathub, dan layanan eksklusif, harga per malam hanya 2.000.000.\n");
    printf("0. Kembali\n");
    getchar();
    getchar();
}


// Fungsi Reservasi Mandiri
//kurang modul input/output
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 5 fungsi, 6 array, 8 input/output
void selfReservation() {
    int roomChoice;
    Customer newCustomer;

    printf("\nReservasi Mandiri:\n");
    printf("1. Kamar Standar\n");
    printf("2. Kamar VIP\n");
    printf("3. Suite\n");
    printf("Masukkan pilihan kamar dalam angka: ");
    scanf("%d", &roomChoice);

    if (roomChoice < 1 || roomChoice > 3) {
        printf("Pilihan tidak valid.\n");
        return;
    }

    printf("Masukkan data pelanggan:\n");
    printf("Nama lengkap: ");
    getchar(); 
    fgets(newCustomer.name, 50, stdin);
    newCustomer.name[strcspn(newCustomer.name, "\n")] = '\0'; 

    printf("Nomor telepon: ");
    scanf("%s", newCustomer.phone);

    printf("NIK atau nomor paspor: ");
    scanf("%s", newCustomer.idNumber);

    printf("Masukan tanggal masuk (dd/mm/yyyy): ");
    scanf("%s", newCustomer.tanggalmasuk);

    printf("Masukan tanggal keluar (dd/mm/yyyy): ");
    scanf("%s", newCustomer.tanggalkeluar);


    if (roomChoice == 1) {
        strcpy(newCustomer.roomType, "Standar");
        newCustomer.price = 500000.0;
    } else if (roomChoice == 2) {
        strcpy(newCustomer.roomType, "VIP");
        newCustomer.price = 1000000.0;
    } else if (roomChoice == 3) {
        strcpy(newCustomer.roomType, "Suite");
        newCustomer.price = 2000000.0;
    }

    customers[customerCount++] = newCustomer;

    printf("Silahkan melakukan konfirmasi pemesanan dan pembayaran pada meja registrasi.\n");
    printf("Selesai.\n");
}


// Customer menu
//selesai
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 4 perulagan, 5 fungsi
void customerMenu() {
    int choice;
    while (1) {
        printf("\nUI Pelanggan\n");
        printf("1. Lihat informasi layanan hotel\n");
        printf("2. Rating\n");
        printf("3. Komentar\n");
        printf("4. Lihat deskripsi kamar\n");
        printf("5. Reservasi mandiri\n");
        printf("0. Kembali\n");
        printf("Masukkan Pilihan: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                hotelServiceInfoCustomer();
                break;
            case 2:
                ratingMenu();
                break;
            case 3:
                commentMenu();
                break;
            case 4:
                roomDescription();
                break;
            case 5:
                selfReservation();
                break;
            case 0:
                return;
            default:
                printf("Pilihan tidak valid. Silahkan coba lagi.\n");
        }
    }
}


// Pause function
void pause() {
    printf("Tekan Enter untuk melanjutkan...");
    getchar();
    getchar();
}
