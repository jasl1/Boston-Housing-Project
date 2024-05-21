import sqlite3

def fetch_data(db_path):
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM housing_data")
    rows = cursor.fetchall()
    conn.close()
    return rows

if __name__ == "__main__":
    data = fetch_data('boston_housing.db')
    for row in data[:5]:  # Print first 5 rows
        print(row)
