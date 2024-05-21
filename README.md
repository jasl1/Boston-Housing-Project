# Boston-Housing-Project
This project defines a machine learning project that predicts housing prices using the well-known Boston Housing dataset. This project will cover all aspects including data storage, retrieval, processing, model training, version control, and automation. We will use the following technologies: SQL, Python, C/C++, Git, and Shell on a Linux environment.

### Project Overview
1. Data Storage: Store the Boston Housing dataset in an SQL database.
2. Data Retrieval: Retrieve the data using SQL.
3. Data Processing: Process the data using C++ for efficiency.
4. Model Training: Train a machine learning model using Python.
5. Version Control: Use Git for version control.
6. Automation and Environment Management: Use Shell scripting to automate tasks and manage the project environment.

### Data Storage
The first step involves storing the Boston Housing dataset in an SQL database to facilitate structured data management and easy retrieval. We used Python's sklearn library to load the dataset and pandas to manipulate it into a DataFrame. We then connected to an SQLite database using the sqlite3 library, created a table named housing_data, and inserted the dataset into this table. This setup ensures that the data is well-organized and can be efficiently queried for subsequent processing and analysis.

```python
import sqlite3
from sklearn.datasets import load_boston
import pandas as pd

# Load Boston Housing dataset
boston = load_boston()
data = pd.DataFrame(boston.data, columns=boston.feature_names)
data['PRICE'] = boston.target

# Connect to SQLite database
conn = sqlite3.connect('boston_housing.db')
c = conn.cursor()

# Create table
c.execute('''
    CREATE TABLE IF NOT EXISTS housing_data (
        ID INTEGER PRIMARY KEY,
        CRIM REAL,
        ZN REAL,
        INDUS REAL,
        CHAS INTEGER,
        NOX REAL,
        RM REAL,
        AGE REAL,
        DIS REAL,
        RAD INTEGER,
        TAX REAL,
        PTRATIO REAL,
        B REAL,
        LSTAT REAL,
        PRICE REAL
    )
''')

# Insert data into the table
data.to_sql('housing_data', conn, if_exists='replace', index_label='ID')

# Close connection
conn.close()

```

### Data Retrieval
The second step focuses on retrieving the stored data from the SQLite database using SQL queries. We wrote a Python script that connects to the SQLite database, executes a SELECT SQL query to fetch all rows from the housing_data table, and retrieves the data. This data retrieval process is crucial for feeding the data into the next steps of the project, such as processing and model training. The script also prints the first few rows to verify the retrieval process.

```python
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

```

### Data Processing
In the third step, we processed the retrieved data using C++ for better performance and efficiency, especially useful for large datasets. We wrote a C++ program that connects to the SQLite database, executes a query to fetch all rows, and stores the data in a custom C++ structure. The program then processes this data, here demonstrated by printing out the ID and Price of each row. This step ensures the data is correctly formatted and ready for model training, leveraging C++'s speed for intensive data handling tasks.

```python
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

```

### Model Training
The fourth step involves training a machine learning model to predict housing prices. Using Python, we reloaded the dataset from the SQLite database, split it into features (independent variables) and the target variable (price). We then divided the data into training and test sets and trained a Linear Regression model using scikit-learn. After training, we evaluated the model's performance on the test set by calculating the Mean Squared Error (MSE). This step is central to developing a predictive model based on the dataset.

```python
import sqlite3
import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error

def load_data(db_path):
    conn = sqlite3.connect(db_path)
    df = pd.read_sql_query("SELECT * FROM housing_data", conn)
    conn.close()
    return df

if __name__ == "__main__":
    df = load_data('boston_housing.db')

    X = df.drop(columns=['ID', 'PRICE'])
    y = df['PRICE']

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    model = LinearRegression()
    model.fit(X_train, y_train)

    y_pred = model.predict(X_test)
    mse = mean_squared_error(y_test, y_pred)

    print(f"Mean Squared Error: {mse}")

```

### Version Control
The fifth step is setting up version control using Git to manage changes to the project files. We initialized a Git repository, added all relevant scripts (for database creation, data retrieval, processing, and model training), and committed these files with a descriptive message. This practice of version control helps in tracking changes, collaborating with others, and maintaining a history of modifications, which is essential for managing any software project effectively.

```python
git init
git add create_database.py retrieve_data.py process_data.cpp train_model.py
git commit -m "Initial commit with database creation, data retrieval, processing, and model training scripts"
```

### Automation and Environment Management
The final step involves creating a shell script to automate the entire workflow of the project. We wrote a run_project.sh script that sequentially executes the Python and C++ scripts developed in previous steps: creating the database, retrieving the data, processing it, and training the model. This script streamlines the process, allowing us to run the entire project with a single command, ensuring consistency, and saving time by automating repetitive tasks. It also helps in setting up the environment and managing dependencies, making it easier to reproduce the project setup.

```python
#!/bin/bash

# Create the database
python3 create_database.py

# Retrieve data
python3 retrieve_data.py > retrieved_data.txt

# Compile and run the C++ processing script
g++ -o process_data process_data.cpp -lsqlite3
./process_data

# Train the model
python3 train_model.py

```
