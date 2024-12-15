import csv
import random
from faker import Faker

# Initialize Faker
fake = Faker()

# Define the number of products
NUM_PRODUCTS = 100

# Define some sample categories, units, and branches
CATEGORIES = ["Electronics", "Furniture", "Clothing", "Groceries", "Toys", "Books"]
UNITS = ["piece", "box", "kg", "meter", "litre"]
BRANCHES = ["Branch A", "Branch B", "Branch C", "Online Store"]


def generate_product_data(num_products):
    products = []
    for _ in range(num_products):
        product = {
            "name": fake.word().capitalize() + " " + fake.word().capitalize(),
            "stock": random.randint(10, 500),
            "price": round(random.uniform(5, 500), 2),  # Random price between $5 and $500
            "unit": random.choice(UNITS),
            "category": random.choice(CATEGORIES),
            "branch": random.choice(BRANCHES),
        }
        products.append(product)
    return products

def save_to_csv(products, filename="data_file/products.csv"):
    with open(filename, mode="w", newline="", encoding="utf-8") as file:
        writer = csv.DictWriter(file, fieldnames=["name", "stock", "price", "unit", "category", "branch"])
        writer.writeheader()
        writer.writerows(products)


if __name__ == "__main__":
    products = generate_product_data(NUM_PRODUCTS)
    save_to_csv(products)
    print(f"{NUM_PRODUCTS} fake products saved to 'products.csv'.")
