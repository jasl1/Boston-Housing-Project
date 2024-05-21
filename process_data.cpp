#include <iostream>
#include <vector>
#include <sqlite3.h>

struct HousingData {
    int id;
    double crim, zn, indus, nox, rm, age, dis, tax, ptratio, b, lstat, price;
    int chas, rad;
};

std::vector<HousingData> fetch_data(const char* db_path) {
    sqlite3* db;
    sqlite3_open(db_path, &db);

    std::vector<HousingData> data;
    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM housing_data";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        HousingData row;
        row.id = sqlite3_column_int(stmt, 0);
        row.crim = sqlite3_column_double(stmt, 1);
        row.zn = sqlite3_column_double(stmt, 2);
        row.indus = sqlite3_column_double(stmt, 3);
        row.chas = sqlite3_column_int(stmt, 4);
        row.nox = sqlite3_column_double(stmt, 5);
        row.rm = sqlite3_column_double(stmt, 6);
        row.age = sqlite3_column_double(stmt, 7);
        row.dis = sqlite3_column_double(stmt, 8);
        row.rad = sqlite3_column_int(stmt, 9);
        row.tax = sqlite3_column_double(stmt, 10);
        row.ptratio = sqlite3_column_double(stmt, 11);
        row.b = sqlite3_column_double(stmt, 12);
        row.lstat = sqlite3_column_double(stmt, 13);
        row.price = sqlite3_column_double(stmt, 14);
        data.push_back(row);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return data;
}

int main() {
    const char* db_path = "boston_housing.db";
    std::vector<HousingData> data = fetch_data(db_path);

    for (const auto& row : data) {
        std::cout << "ID: " << row.id << ", Price: " << row.price << std::endl;
    }

    return 0;
}
