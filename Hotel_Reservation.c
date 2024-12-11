#include <stdio.h>//Library standar untuk operasi input dan output
#include <string.h>//Library untuk manipulasi string, seperti strcpy(), strlen()
#include <stdlib.h>//Library standar untuk fungsi-fungsi umum seperti malloc(), free(), dan system()

#define MAX_ROOMS 100//define mendefinisikan konstanta
#define MAX_CUSTOMERS 100

//uji regristrasi
#define MAX_ADMIN 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Makro untuk membersihkan layar
#ifdef _WIN32//Memeriksa apakah program dijalankan pada sistem Windows.
    #define CLEAR_SCREEN() system("cls")//membersihkan layar di Windows menggunakan perintah cls
#else
    #define CLEAR_SCREEN() system("clear")//membersihkan layar di sistem non-Windows menggunakan perintah clear
#endif

//uji regristrasi
// Struktur untuk data admin
typedef struct {
    int id;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} Admin;

// uji deklarasi variabel regristrasi
Admin admins[MAX_ADMIN];
int adminCount = 0;

// uji
#define MAX_SERVICES 100

typedef struct {
    char serviceName[50];
    char contact[20];
} Service;

Service services[MAX_SERVICES];
int serviceCount = 0;

typedef struct {//menyimpan data kamar
    int roomNumber;
    char type[20];
    int isAvailable; // 1 = tersedia, 0 = terisi
} Room;

typedef struct {//menyimpan data pelanggan
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


Admin admins[MAX_CUSTOMERS];//Array Global
Room rooms[MAX_ROOMS];
Customer customers[MAX_CUSTOMERS];
Service services[MAX_SERVICES];


int roomCount = 0, customerCount = 0;//Variabel global untuk melacak jumlah admin, kamar, pelanggan, dan layanan yang sudah terdaftar.

// Deklarasi Prototipe Fungsi
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
        CLEAR_SCREEN();
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
// Fungsi registrasi admin
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


// Room data menu (menambah, menghapus, dan memperbarui status kamar)
//kurang modul input/output
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 4 perulagan, 5 fungsi, 6 array, 8 input/output
void dataRoomMenu() {
    int choice;//untuk input pilihan
    do {
        system("cls");
        printf("=== Data Kamar ===\n");
        for (int i = 0; i < roomCount; i++) {//perulagan untuk menampilkan setiap data kamar
            printf("Kamar No: %d, Tipe: %s, Status: %s\n", 
                rooms[i].roomNumber, //no kamar
                rooms[i].type, //tipe kamar
                rooms[i].isAvailable ? "Kosong" : "Terisi");//tersedia atau terisi
        }

        printf("\n1. Tambah Kamar\n");
        printf("2. Hapus Kamar\n");
        printf("3. Update Status Kamar\n");
        printf("0. Kembali\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            if (roomCount >= MAX_ROOMS) {//jika jumlah kamar telah mencapai batas maksimal
                printf("Kapasitas kamar penuh!\n");
            } else {
                printf("Masukkan nomor kamar: ");
                scanf("%d", &rooms[roomCount].roomNumber);//input pada array roomNumber akan disimpan pada bagian rooms[roomCount]
                printf("Masukkan tipe kamar (standar/VIP/suite): ");
                scanf("%s", rooms[roomCount].type);
                rooms[roomCount].isAvailable = 1; // Default: kosong
                roomCount++;
                printf("Kamar berhasil ditambahkan!\n");
            }
            pause();
            break;
        }
        case 2: {//untuk hapus kamar
            int roomNumber, found = 0;
            printf("Masukkan nomor kamar yang akan dihapus: ");
            scanf("%d", &roomNumber);//membaca input

            for (int i = 0; i < roomCount; i++) {//mencari kamar dengan no yang di input dengan perulangan
                if (rooms[i].roomNumber == roomNumber) {//jika terdapat no yang sama dengan yang di inpuut
                    for (int j = i; j < roomCount - 1; j++) {//
                        rooms[j] = rooms[j + 1];
                    }
                    roomCount--;//mengurangi jumlah total kamar
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
        case 3: {//merubah status
            int roomNumber, found = 0;
            printf("Masukkan nomor kamar yang statusnya akan diperbarui: ");
            scanf("%d", &roomNumber);//membaca input

            for (int i = 0; i < roomCount; i++) {//mencari no kamar
                if (rooms[i].roomNumber == roomNumber) {
                    rooms[i].isAvailable = !rooms[i].isAvailable;//fungsi untuk merubah (membalik) status kamar
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
         loadSelfReservation();
        for (int i = 0; i < customerCount; i++) {//menampilkan output data pelaggan secara berulang
            printf("Pelanggan %d:\n", i + 1);
            printf("Nama Lengkap: %s\n", customers[i].name);//menampilkan informasi yang tersimpan di array
            printf("Nomor Telepon: %s\n", customers[i].phone);
            printf("NIK/Paspor: %s\n", customers[i].idNumber);
            printf("Tipe Kamar: %s\n", customers[i].roomType);
            printf("Harga Kamar: %d\n\n", customers[i].price);
            printf("tanggal masuk (dd/mm/yyyy): %s\n", customers[i].tanggalmasuk);
            printf("tanggal keluar (dd/mm/yyyy): %s\n\n", customers[i].tanggalkeluar);
        }

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
//perlu dikerjakan
//kurang modul input/output
//terdiri atas modul 2 sintaks dasar, 5 fungsi, 6 array, 8 input/output
void ratingMenu() {
    system("cls");
    int rating;
    int totalRating = 0;
    int jumlahPengguna = 0;
    float Ratarata;
    char pilihan;

    const char *ratingan = "hasil_rating.txt";
    FILE *file;

    printf("Ratingan hotel\n");

    do {
        printf("berikan Rating (1-5): ");
        scanf("%d",&rating);

        if(rating <1 || rating >5){
            printf("rating tidak valid, harap masukkan angka 1-5.\n");
            continue;
        }
        totalRating += rating;
        jumlahPengguna++;
        printf("terimakasih atass ratingan anda: %d\n", rating);

        printf("apakah anda ingin memberikan ratingan lagi? (y/n): ");
        scanf(" %c", &pilihan);

    }while (pilihan == 'y');

    if(jumlahPengguna > 0){
        Ratarata = (float)totalRating / jumlahPengguna;
        printf("\n=== statistik rating ===\n");
        printf("jumlah pengguna: %d\n", jumlahPengguna);
        printf("total rating : %.2f\n", Ratarata);

        file = fopen(ratingan, "w");
        if(file == NULL) {
            printf("Gagal membuka file untuk menyimpan data.\n");
            return 1;
        }

        fprintf(file, "=== Statistik Rating ===\n");
        fprintf(file, "jumlah Pengguna: %d\n", jumlahPengguna);
        fprintf(file, "Rata-rata rating: %.2f\n", Ratarata);
        fclose(file);

        printf("\nHasil telah disimpan ke file '%s'.\n", ratingan);
    }else {
        printf("\nbelum ada rating yang diberikan.\n");
    }

    printf("terimah kasih telah memberikan ratingan!\n");
    getchar();
    getchar();
}


// Fungsi Menu Komentar
//perlu dikerjakan
//kurang modul input/output
//terdiri atas modul 2 sintaks dasar, 5 fungsi, 6 array, 8 input/output
void commentMenu() {
    system("cls");

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
    system("cls");
    printf("\nDeskripsi Kamar:\n");
    printf("1. Standar: Kamar luas 6x6 meter dengan kasur untuk 2 orang, harga per malam hanya 500.000.\n");
    printf("2. VIP: Kamar luas10x10 meter dengan fasilitas kamar mandi bathub, harga per malam hanya 1.000.000.\n");
    printf("3. Suite: Kamar luas 12x12 meter dengan pemandangan indah, kamar mandi bathub, dan layanan eksklusif, harga per malam hanya 2.000.000.\n");
    printf("0. Kembali\n");
    getchar();
    getchar();
}


// Fungsi Reservasi Mandiri
//selesai
//terdiri atas modul 2 sintaks dasar, 3 percabagan, 5 fungsi, 6 array, 8 input/output
void selfReservation() {
    CLEAR_SCREEN();
    int roomChoice;
    Customer newCustomer;

    printf("\nReservasi Mandiri:\n");
    printf("1. Kamar Standar\n");
    printf("2. Kamar VIP\n");
    printf("3. Suite\n");
    printf("Masukkan pilihan kamar dalam angka: ");
    scanf("%d", &roomChoice);

    if (roomChoice < 1 || roomChoice > 3) {//jika pilihan kamar kurang dari 1 dan lebih dari 3 maka aman menampilkan yang dibawah
        printf("Pilihan tidak valid.\n");
        return;
    }

    printf("Masukkan data pelanggan:\n");
    printf("Nama lengkap: ");
    getchar(); 
    fgets(newCustomer.name, 50, stdin);//membaca nama
    newCustomer.name[strcspn(newCustomer.name, "\n")] = '\0'; //hapus (new line \n)

    printf("Nomor telepon: ");
    scanf("%s", newCustomer.phone); //memasukkan nomor telepon

    printf("NIK atau nomor paspor: ");
    scanf("%s", newCustomer.idNumber); //memasukkan NIK atau no paspor

    printf("Masukan tanggal masuk (dd/mm/yyyy): ");
    scanf("%s", newCustomer.tanggalmasuk); //memasukkan tgl masuk

    printf("Masukan tanggal keluar (dd/mm/yyyy): ");
    scanf("%s", newCustomer.tanggalkeluar); //memasukkan tgl keluar


    if (roomChoice == 1) {//fungsi pilihan kamar....jika pilih 1 akan menampilkan standar
        strcpy(newCustomer.roomType, "Standar");
        newCustomer.price = 500000.0;
    } else if (roomChoice == 2) {//jika pilih 2 akan menampilkan
        strcpy(newCustomer.roomType, "VIP");
        newCustomer.price = 1000000.0;
    } else if (roomChoice == 3) {//jika pilih 3 akan menampilkan
        strcpy(newCustomer.roomType, "Suite");
        newCustomer.price = 2000000.0;
    }

    customers[customerCount++] = newCustomer;

    printf("Silahkan melakukan konfirmasi pemesanan dan pembayaran pada meja registrasi.\n");
    printf("Selesai.\n");
}
void saveSelfReservation() {
    Customer newCustomer;
    FILE *data;
    data = fopen("reservasi_mandiri.dat", "wb");
    if (data == NULL) {
        printf("Error: Tidak dapat menyimpan data.\n");
        return;
    }
    fwrite(&newCustomer, sizeof(newCustomer), 1, data);
    fclose(data);
}

// Fungsi untuk membaca data dari file
void loadSelfReservation() {
    Customer newCustomer;
    FILE *data;
    data = fopen("reservasi_mandiri.dat", "rb");
    if (data == NULL) {
        printf("Tidak ada file data ditemukan. Memulai dengan data kosong.\n");
        return;
    }
    fread(&newCustomer, sizeof(newCustomer), 1, data);
    fclose(data);
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
