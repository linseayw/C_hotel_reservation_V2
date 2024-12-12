#include <stdio.h>//Library standar untuk operasi input dan output
#include <string.h>//Library untuk manipulasi string, seperti strcpy(), strlen()
#include <stdlib.h>//Library standar untuk fungsi-fungsi umum seperti malloc(), free(), dan system()

// data kamar
#define MAX_ROOMS 100//define mendefinisikan konstanta

// data MAX_CUSTOMERS
#define MAX_CUSTOMERS 100

// regristrasi
#define MAX_ADMIN 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// input service
#define MAX_SERVICES 100

// comment
#define MAX_COMMENTS 100

// input deskripsi kamar
#define MAX_DESCRIPTIONS 100
#define MAX_LENGTH 50

// ratting
#define MAX_USERS 100

// Makro untuk membersihkan layar
#ifdef _WIN32//Memeriksa apakah program dijalankan pada sistem Windows.
    #define CLEAR_SCREEN() system("cls")//membersihkan layar di Windows menggunakan perintah cls
#else
    #define CLEAR_SCREEN() system("clear")//membersihkan layar di sistem non-Windows menggunakan perintah clear
#endif

// input deskropsi
typedef struct {
    char type[MAX_LENGTH];
    char facility[MAX_LENGTH];
    float price;
} Description;
Description descriptions[MAX_DESCRIPTIONS];
int descriptionCount = 0;


// deklarasi comment
typedef struct {
    char customerName[50];
    char comment[255];
} Comment;
Comment comments[MAX_COMMENTS];
int commentCount = 0;


// regristrasi
// Struktur untuk data admin
typedef struct {
    int id;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} Admin;
// variabel regristrasi
Admin admins[MAX_ADMIN];
int adminCount = 0;


// menyimpan input Service
typedef struct {
    char serviceName[50];
    char contact[20];
} Service;
Service services[MAX_SERVICES];
int serviceCount = 0;


//menyimpan data kamar
typedef struct {
    int roomNumber;
    char type[20];
    int isAvailable; // 1 = tersedia, 0 = terisi
} Room;


//menyimpan data pelanggan
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
Customer customers[MAX_CUSTOMERS];

// simpan ratting
typedef struct {
    char customerName[100];
    int rating;
} Rating;
Rating ratings[MAX_USERS];
int ratingCount = 0;


Admin admins[MAX_CUSTOMERS];//Array Global
Room rooms[MAX_ROOMS];


int roomCount = 0, customerCount = 0;//Variabel global untuk melacak jumlah kamar, pelanggan

// Deklarasi Prototipe Fungsi
//switch case
void mainMenu();//r //switch case utama (pelanggan atau admin)

void adminMenu();//r //switch case admin (regristrasi atau login)
void adminProgram();//r //switch case admin (fitur admin)

void customerMenu();//r //switch case (Fitur Pelanggan)

void adminRegistration();//r
void adminLogin();//kurang membuat kunci max 3 kali

void dataRoomMenu();//r
void dataCustomerMenu();
void paymentReportMenu();
void visitReportMenu();
void hotelServicesMenu();//r
void InputDescription();//r

void hotelServiceInfoCustomer();//r
void ratingMenu();//r
void commentMenu();//r
void roomDescription();//r
void selfReservation();//r


void pause();//fungsi untuk menghentikan sementara program (menunggu input user).

//bagian untuk fungsi uji coba



// Main function
int main() {//Fungsi utama program, di mana eksekusi dimulai.
    mainMenu();
    return 0;
}


// Main menu
//selesai
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 4 perulagan, 5 fungsi
void mainMenu() {
    int choice;
    do {//menggunakan perulangan do-while untuk keluar 
        system("cls");
        printf("Selamat datang di hotel Kel 41 EL03\n");
        printf("Silahkan pilih:\n");
        printf("1. Admin\n");
        printf("2. Pelanggan\n");
        printf("0. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {//switch case digunakan untuk mengeksekusi program berdasarkan pilihan
        case 1:
            adminMenu();
            break;
        case 2:
            customerMenu();
            break;
        
        case 0://jika memilih 0 maka akan mengakhiri program
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
        case 0://jika memilih 0 maka akan kembali ke fungsi sebelumnya
            return;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
            pause();
        }
    } while (choice != 0);
}


// Fungsi untuk memuat data admin dari file
void loadAdminsFromFile() {
    FILE *myfile = fopen("Registrasi.dat", "rb");  // Buka file untuk membaca data admin
    if (myfile != NULL) {
        while (fread(&admins[adminCount], sizeof(Admin), 1, myfile)) {
            adminCount++;  // Meningkatkan jumlah admin yang terdaftar
        }
        fclose(myfile);  // Tutup file setelah membaca
    } else {
        printf("Error opening file to load admins.\n");
    }
}

// Fungsi untuk mencatat log aktivitas
void data_log(const char *user, const char *activity) {
    FILE *logfile = fopen("log.txt", "a");
    if (logfile != NULL) {
        fprintf(logfile, "User: %s Activity: %s\n", user, activity);
        fclose(logfile);
    }
}

// Admin registration
//terdiri atas modul 2 sintaks dasar, 5 fungsi, 6 array, 8 input/output
// selesai
void adminRegistration() {
    system("cls");  // Bersihkan layar (untuk Windows)
    FILE *myfile;

    // Buka file untuk membaca data admin (opsional jika ingin validasi)
    myfile = fopen("Registrasi.dat", "ab");  // Mode append binary untuk menambah data ke file
    if (myfile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("UI Registrasi\n");
    printf("Silahkan masukkan ID: ");
    admins[adminCount].id = adminCount + 1;  // Menetapkan ID admin
    printf("%d\n", admins[adminCount].id);   // Output ID admin yang telah ditetapkan

    printf("Silahkan masukkan username baru: ");
    scanf("%49s", admins[adminCount].username);  // Input username (mencegah buffer overflow)

    printf("Silahkan masukkan password: ");
    scanf("%49s", admins[adminCount].password);  // Input password (mencegah buffer overflow)

    printf("Selamat, Anda telah berhasil mendaftar! Silahkan login.\n");

    // Simpan data admin ke file
    fwrite(&admins[adminCount], sizeof(Admin), 1, myfile);
    adminCount++;  // Meningkatkan jumlah admin yang terdaftar

    fclose(myfile);  // Tutup file

    data_log(admins[adminCount - 1].username, "adminRegistration");  // Log aktivitas

    adminMenu();  // Panggil menu operator setelah registrasi
    pause();  // Tunggu input pengguna
}

// Fungsi untuk login admin
// kurang membuat kunci max 3 kali coba
void adminLogin() {
    char username[50], password[50];  // Array char untuk menyimpan username dan password
    int found = 0;  // Memeriksa apakah login gagal

    system("cls");
    printf("UI Login\n");

    // Memuat data admin dari file sebelum login
    loadAdminsFromFile();  // Memastikan data admin terload sebelum login

    printf("Silahkan masukkan username: ");
    scanf("%s", username);
    printf("Silahkan masukkan password: ");
    scanf("%s", password);

    for (int i = 0; i < adminCount; i++) {  // Perulangan untuk melakukan pengecekan pada seluruh input admin
        if (strcmp(admins[i].username, username) == 0) {  // strcmp fungsi untuk membandingkan string
            if (strcmp(admins[i].password, password) == 0) {
                found = 1;
                printf("Selamat datang %s\n", admins[i].username);
                pause();
                // Panggil fungsi program admin setelah login sukses
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
        printf("6. Input deskripsi tipe kamar\n");
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
        case 6:
            InputDescription();
            break;
        case 0:
            return;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
            pause();
        }
    } while (choice != 0);
}


// Room data menu (menambah, menghapus, dan memperbarui status kamar)
//selesai
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 4 perulagan, 5 fungsi, 6 array, 8 input/output
void dataRoomMenu() {
    int choice;
    do {
        system("cls");
        printf("=== Data Kamar ===\n");
        loadRoomsFromFile();
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
                rooms[roomCount].isAvailable = 1; // Default: Kosong
                roomCount++;
                printf("Kamar berhasil ditambahkan!\n");
                saveRoomsToFile();
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
                    saveRoomsToFile();
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
                    saveRoomsToFile();
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
            saveRoomsToFile();
            return;
        default:
            printf("Pilihan tidak valid.\n");
            pause();
        }
    } while (choice != 0);
}

void saveRoomsToFile() {
    FILE *file = fopen("rooms.dat", "wb");
    if (file == NULL) {
        printf("Error: Tidak dapat menyimpan data kamar.\n");
        return;
    }
    fwrite(&roomCount, sizeof(int), 1, file);
    fwrite(rooms, sizeof(Room), roomCount, file);
    fclose(file);
}

void loadRoomsFromFile() {
    FILE *file = fopen("rooms.dat", "rb");
    if (file == NULL) {
        printf("Tidak ada file data kamar ditemukan. Memulai dengan data kosong.\n");
        return;
    }
    fread(&roomCount, sizeof(int), 1, file);
    fread(rooms, sizeof(Room), roomCount, file);
    fclose(file);
}


// Customer data menu
//kurang modul input/output
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 4 perulagan, 5 fungsi, 6 array, 8 input/output
void dataCustomerMenu() {
    int choice;
    do {
         loadSelfReservation();
        system("cls");
    printf("=== Daftar Reservasi ===\n");
    if (customerCount == 0) {
        printf("Belum ada reservasi.\n");
    } else {
        for (int i = 0; i < customerCount; i++) {
            printf("%d. Nama: %s\n", i + 1, customers[i].name);
            printf("   Telepon: %s\n", customers[i].phone);
            printf("   NIK/Paspor: %s\n", customers[i].idNumber);
            printf("   Tanggal Masuk: %s\n", customers[i].tanggalmasuk);
            printf("   Tanggal Keluar: %s\n", customers[i].tanggalkeluar);
            printf("   Tipe Kamar: %s\n", customers[i].roomType);
            printf("   Harga Kamar: %d\n", customers[i].price);
            printf("-----------------------------\n");
        }}

        printf("\n1. Hapus Pelanggan\n");
        printf("0. Kembali\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {//hapus palaggan
            int index;
            printf("Masukkan nomor pelanggan yang akan dihapus: ");
            scanf("%d", &index);
            if (index < 1 || index > customerCount) { //jika nomor tidak ditemukan
                printf("Pelanggan tidak ditemukan.\n");
            } else {
                for (int i = index - 1; i < customerCount - 1; i++) {//perulahan for digunakan untuk menggeser jika nomor pelanggan yang akan dihapus ditemukan
                    customers[i] = customers[i + 1];
                }
                customerCount--;
                printf("Pelanggan berhasil dihapus.\n");
                saveSelfReservation();
            }
            pause();
            break;
        }
        case 0:
            saveSelfReservation();
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
            printf("-----------------------------\n");
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
    int choice;
    do
    {
    
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
        if (strcmp(currentDate, customers[i].tanggalmasuk) != 0) {//Membandingkan tanggal saat ini yang disimpan dalam currentDate dengan tanggal masuk pelanggan pada indeks i (customers[i].tanggalmasuk).
            if (strlen(currentDate) > 0) {//Mengecek apakah currentDate sudah terisi. Jika sudah ada tanggal sebelumnya, maka akan mencetak baris kosong (\n) untuk pemisah
                printf("\n"); 
            }
            strcpy(currentDate, customers[i].tanggalmasuk);//Menyalin tanggal masuk pelanggan saat ini ke dalam variabel currentDate untuk dibandingkan pada iterasi berikutnya
            printf("Tanggal %s\n", currentDate);
        }
        printf("- %s\n", customers[i].name); // Tampilkan nama pelanggan
        totalVisitors++;//Menambah variabel totalVisitors setiap kali ada nama pelanggan yang ditampilkan
    }

    printf("\nTotal pengunjung: %d\n", totalVisitors);
    printf("0. Keluar\n");
    printf("Pilihan Anda: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 0 :
        return;
    default:
            printf("Pilihan tidak valid.\n");
            pause();
    }

    } while (choice != 0);
}


// Hotel services menu bagian ADMIN, untuk melakukan input 
//selesai
//SUDAH TERUHUBUNG Hotel services menu PELANGGAN
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 4 perulagan, 5 fungsi, 6 array, 8 input/output
void hotelServicesMenu() {
    int choice;
    do {
        system("cls");
        printf("=== Informasi Layanan Hotel ===\n");
        loadServicesFromFile();
        for (int i = 0; i < serviceCount; i++) {
            printf("Layanan: %s, Kontak: %s\n", services[i].serviceName, services[i].contact);
        }

        printf("\n1. Tambahkan Layanan\n");
        printf("2. Hapus Layanan\n");
        printf("0. Kembali\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: { // Menambah layanan hotel
            if (serviceCount >= MAX_SERVICES) {
                printf("Kapasitas layanan penuh!\n");
            } else {
                printf("Masukkan nama layanan: ");
                scanf(" %[^\n]", services[serviceCount].serviceName);
                printf("Masukkan kontak layanan: ");
                scanf("%s", services[serviceCount].contact);
                serviceCount++;
                printf("Layanan berhasil ditambahkan!\n");
                saveServicesToFile(); // Simpan perubahan ke file
            }
            pause();
            break;
        }
        case 2: { // Menghapus layanan
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
                    saveServicesToFile(); // Simpan perubahan ke file
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
            saveServicesToFile(); // Pastikan perubahan tersimpan saat keluar
            return;
        default:
            printf("Pilihan tidak valid.\n");
            pause();
        }
    } while (choice != 0);
}

void saveServicesToFile() {
    FILE *file = fopen("services.dat", "wb");
    if (file == NULL) {
        printf("Error: Tidak dapat menyimpan data.\n");
        return;
    }
    fwrite(&serviceCount, sizeof(int), 1, file);
    fwrite(services, sizeof(Service), serviceCount, file);
    fclose(file);
}

// Fungsi untuk membaca data dari file
void loadServicesFromFile() {
    FILE *file = fopen("services.dat", "rb");
    if (file == NULL) {
        printf("Tidak ada file data ditemukan. Memulai dengan data kosong.\n");
        return;
    }
    fread(&serviceCount, sizeof(int), 1, file);
    fread(services, sizeof(Service), serviceCount, file);
    fclose(file);
}

//input room sedkripsi
void InputDescription() {
    int choice;
    do {
        system("cls");
        printf("=== Menu Deskripsi Kamar Hotel ===\n");
        loadDescriptionsFromFile();

        printf("\nDaftar Deskripsi:\n");
        for (int i = 0; i < descriptionCount; i++) {
            printf("%d. Tipe kamar: %s, Fasilitas: %s, Harga: %.2f\n", i + 1, descriptions[i].type, descriptions[i].facility, descriptions[i].price);
        }

        printf("\n1. Tambah Deskripsi\n");
        printf("2. Hapus Deskripsi\n");
        printf("0. Kembali\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: { // Tambah Deskripsi
            if (descriptionCount >= MAX_DESCRIPTIONS) {
                printf("Kapasitas deskripsi penuh!\n");
            } else {
                printf("Masukkan tipe layanan: ");
                scanf(" %[^\n]", descriptions[descriptionCount].type);
                printf("Masukkan fasilitas layanan: ");
                scanf(" %[^\n]", descriptions[descriptionCount].facility);
                printf("Masukkan harga layanan: ");
                scanf("%f", &descriptions[descriptionCount].price);
                descriptionCount++;
                printf("Deskripsi berhasil ditambahkan!\n");
                saveDescriptionsToFile(); // Simpan perubahan ke file
            }
            pause();
            break;
        }
        case 2: { // Hapus Deskripsi
            int number;
            printf("Masukkan nomor deskripsi yang akan dihapus: ");
            scanf("%d", &number);

            if (number < 1 || number > descriptionCount) {
                printf("Nomor deskripsi tidak valid!\n");
            } else {
                for (int i = number - 1; i < descriptionCount - 1; i++) {
                    descriptions[i] = descriptions[i + 1];
                }
                descriptionCount--;
                printf("Deskripsi berhasil dihapus.\n");
                saveDescriptionsToFile(); // Simpan perubahan ke file
            }
            pause();
            break;
        }
        case 0:
            saveDescriptionsToFile(); // Simpan saat keluar
            return;
        default:
            printf("Pilihan tidak valid.\n");
            pause();
        }
    } while (choice != 0);
}

void saveDescriptionsToFile() {
    FILE *file = fopen("descriptions.dat", "wb");
    if (file == NULL) {
        printf("Error: Tidak dapat menyimpan data.\n");
        return;
    }
    fwrite(&descriptionCount, sizeof(int), 1, file);
    fwrite(descriptions, sizeof(Description), descriptionCount, file);
    fclose(file);
}

void loadDescriptionsFromFile() {
    FILE *file = fopen("descriptions.dat", "rb");
    if (file == NULL) {
        printf("Tidak ada file data ditemukan. Memulai dengan data kosong.\n");
        return;
    }
    fread(&descriptionCount, sizeof(int), 1, file);
    fread(descriptions, sizeof(Description), descriptionCount, file);
    fclose(file);
}


// Fungsi Informasi Layanan Hotel bagian pelanggan
//selesai
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 4 perulagan, 5 fungsi
void hotelServiceInfoCustomer() {
    system("cls"); 
    printf("=== Informasi Layanan Hotel ===\n");

    loadServicesFromFile();
    
    if (serviceCount == 0) {//pemeriksaan kondisi serviceCount sama-sama dengan 0
        printf("Belum ada layanan yang tersedia.\n");
    } else {
        for (int i = 0; i < serviceCount; i++) {//menggunakan perulangan for untuk perulangan layanan yang tersedia sebanyak serviceCount
            printf("Layanan: %s, Kontak: %s\n", services[i].serviceName, services[i].contact);
        }
    }

    printf("0. Kembali\n");
    
    getchar();
    getchar(); 
}


// Fungsi Menu Rating
//selesai
//terdiri atas modul 2 sintaks dasar, 5 fungsi, 6 array, 8 input/output
void ratingMenu() {
    int choice;
    do {
        system("cls");
        printf("=== Menu Rating ===\n");
        loadRatingsFromFile();

        // Menampilkan daftar rating
        if (ratingCount > 0) {
            printf("\nDaftar Rating:\n");
            for (int i = 0; i < ratingCount; i++) {
                printf("%d. [%s] Rating: %d\n", i + 1, ratings[i].customerName, ratings[i].rating);
            }
        } else {
            printf("\nBelum ada rating.\n");
        }

        // Menampilkan rata-rata rating
        if (ratingCount > 0) {
            double averageRating = 0.0;
            for (int i = 0; i < ratingCount; i++) {
                averageRating += ratings[i].rating;
            }
            averageRating /= ratingCount;
            printf("\nRata-rata Rating: %.2f\n", averageRating);
            printf("Jumlah Pengguna: %d\n", ratingCount);
        }

        // Menu
        printf("\n1. Tambahkan Rating\n");
        printf("0. Kembali\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: { // Menambahkan rating
            if (ratingCount >= MAX_USERS) {
                printf("Kapasitas rating penuh!\n");
            } else {
                printf("Masukkan nama pelanggan: ");
                scanf(" %[^\n]", ratings[ratingCount].customerName);
                int rating;
                do {
                    printf("Masukkan rating (1-5): ");
                    scanf("%d", &rating);
                    if (rating < 1 || rating > 5) {
                        printf("Rating tidak valid. Harap masukkan angka antara 1 hingga 5.\n");
                    }
                } while (rating < 1 || rating > 5);
                ratings[ratingCount].rating = rating;
                ratingCount++;
                printf("Rating berhasil ditambahkan!\n");
                saveRatingsToFile();
            }
            system("pause");
            break;
        }
        case 0:
            saveRatingsToFile();
            return;
        default:
            printf("Pilihan tidak valid.\n");
            system("pause");
        }
    } while (choice != 0);
}

void saveRatingsToFile() {
    FILE *file = fopen("ratings.dat", "wb");
    if (file == NULL) {
        printf("Error: Tidak dapat menyimpan data.\n");
        return;
    }
    fwrite(&ratingCount, sizeof(int), 1, file);
    fwrite(ratings, sizeof(Rating), ratingCount, file);
    fclose(file);
}

void loadRatingsFromFile() {
    FILE *file = fopen("ratings.dat", "rb");
    if (file == NULL) {
        printf("Tidak ada file data ditemukan. Memulai dengan data kosong.\n");
        return;
    }
    fread(&ratingCount, sizeof(int), 1, file);
    fread(ratings, sizeof(Rating), ratingCount, file);
    fclose(file);
}


// Fungsi Menu Komentar
//selesai
//terdiri atas modul 2 sintaks dasar, 5 fungsi, 6 array, 8 input/output
void commentMenu() {
int choice;
    do {
        system("cls");
        printf("=== Menu Komentar Pelanggan ===\n");
        loadCommentsFromFile();

        // Menampilkan komentar
        if (commentCount > 0) {
            printf("\nDaftar Komentar:\n");
            for (int i = 0; i < commentCount; i++) {
                printf("%d. [%s] %s\n", i + 1, comments[i].customerName, comments[i].comment);
            }
        } else {
            printf("\nBelum ada komentar.\n");
        }

        // Menu
        printf("\n1. Tambahkan Komentar\n");
        printf("2. Hapus Komentar\n");
        printf("0. Kembali\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: { // Menambahkan komentar
            if (commentCount >= MAX_COMMENTS) {
                printf("Kapasitas komentar penuh!\n");
            } else {
                printf("Masukkan nama pelanggan: ");
                scanf(" %[^\n]", comments[commentCount].customerName);
                printf("Masukkan komentar: ");
                scanf(" %[^\n]", comments[commentCount].comment);
                commentCount++;
                printf("Komentar berhasil ditambahkan!\n");
                saveCommentsToFile();
            }
            pause();
            break;
        }
        case 2: { // Menghapus komentar
            int index;
            printf("Masukkan nomor komentar yang akan dihapus: ");
            scanf("%d", &index);
            if (index < 1 || index > commentCount) {
                printf("Nomor komentar tidak valid.\n");
            } else {
                for (int i = index - 1; i < commentCount - 1; i++) {
                    comments[i] = comments[i + 1];
                }
                commentCount--;
                printf("Komentar berhasil dihapus.\n");
                saveCommentsToFile();
            }
            pause();
            break;
        }
        case 0:
            saveCommentsToFile();
            return;
        default:
            printf("Pilihan tidak valid.\n");
            pause();
        }
    } while (choice != 0);
}

void saveCommentsToFile() {
    FILE *file = fopen("comments.dat", "wb");
    if (file == NULL) {
        printf("Error: Tidak dapat menyimpan data.\n");
        return;
    }
    fwrite(&commentCount, sizeof(int), 1, file);
    fwrite(comments, sizeof(Comment), commentCount, file);
    fclose(file);
}

void loadCommentsFromFile() {
    FILE *file = fopen("comments.dat", "rb");
    if (file == NULL) {
        printf("Tidak ada file data ditemukan. Memulai dengan data kosong.\n");
        return;
    }
    fread(&commentCount, sizeof(int), 1, file);
    fread(comments, sizeof(Comment), commentCount, file);
    fclose(file);
}


// Fungsi Deskripsi Kamar
//selesai
//terdiri atas modul 2 sintaks dasar, 5 fungsi
void roomDescription() {
    
        system("cls");
        printf("=== Menu Deskripsi Kamar Hotel ===\n");
        loadDescriptionsFromFile();

        printf("\nDaftar Deskripsi:\n");
        for (int i = 0; i < descriptionCount; i++) {
            printf("%d. Tipe kamar: %s, Fasilitas: %s, Harga: %.2f\n", i + 1, descriptions[i].type, descriptions[i].facility, descriptions[i].price);
        }

        printf("0. Kembali\n");
        printf("Pilihan Anda: ");
    
    getchar();
    getchar(); 
}


// Fungsi Reservasi Mandiri
//selesai
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 5 fungsi, 6 array, 8 input/output
void selfReservation() {
   system("cls");
    loadSelfReservation(); // Memuat data yang ada sebelumnya
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
    saveSelfReservation(); // Simpan data setelah input
    printf("\nReservasi berhasil disimpan!\n");
    printf("Silahkan melakukan konfirmasi pemesanan dan pembayaran pada meja registrasi.\n");
    printf("Selesai.\n");
}

void saveSelfReservation() {
    FILE *file = fopen("reservations.dat", "wb");
    if (file == NULL) {
        printf("Error: Tidak dapat menyimpan data.\n");
        return;
    }
    fwrite(&customerCount, sizeof(int), 1, file);
    fwrite(customers, sizeof(Customer), customerCount, file);
    fclose(file);
}

void loadSelfReservation() {
    FILE *file = fopen("reservations.dat", "rb");
    if (file == NULL) {
        printf("Tidak ada file data ditemukan. Memulai dengan data kosong.\n");
        return;
    }
    fread(&customerCount, sizeof(int), 1, file);
    fread(customers, sizeof(Customer), customerCount, file);
    fclose(file);
}


// Customer menu
//selesai
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 4 perulagan, 5 fungsi
void customerMenu() {
    system("cls");
    
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
void pause() {//digunakan untuk memberikan jeda dalam program dengan menampilkan pesan "Tekan Enter untuk melanjutkan..."
    printf("Tekan Enter untuk melanjutkan...");
    getchar();
    getchar();
}
