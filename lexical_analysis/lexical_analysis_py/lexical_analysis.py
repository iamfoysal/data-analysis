import re
from collections import defaultdict

def classify_tokens(input_line):
    keywords = {"if", "else", "int", "float", "return", "for", "while", "do", "switch", "case"}
    arithmetic_operators = {"+", "-", "*", "/", "="}
    logical_operators = {">", ">=", "<", "<=", "==", "!="}
    punctuation = {";", ":", ","}
    parentheses = {"(", ")", "{", "}", "[", "]"}

    # Regex patterns
    identifier_pattern = re.compile(r"^[a-zA-Z_][a-zA-Z0-9_]*$") 
    constant_pattern = re.compile(r"^\d+$") \
    

    # Token classification
    tokens = re.findall(r"\w+|\S", input_line) # split the input line into words and non-whitespace characters
    
    classified_tokens = defaultdict(list)  # empty list for each category

    for token in tokens:
        if token in keywords:
            classified_tokens["Keyword"].append(token)
        elif token in arithmetic_operators:
            classified_tokens["Arithmetic Operator"].append(token)
        elif token in logical_operators:
            classified_tokens["Logical Operator"].append(token)
        elif token in punctuation:
            classified_tokens["Punctuation"].append(token)
        elif token in parentheses:
            classified_tokens["Parenthesis"].append(token)
        elif constant_pattern.match(token): # or use isdigit()
            classified_tokens["Constant"].append(token)
        elif identifier_pattern.match(token): # or use isidentifier()
            classified_tokens["Identifier"].append(token)
        else:
            classified_tokens["Unknown"].append(token)

    return classified_tokens

def format_output(classified_tokens):
    output = []
    for category, tokens in classified_tokens.items():
        unique_tokens = sorted(set(tokens))
        output.append(f"{category} ({len(unique_tokens)}): {', '.join(unique_tokens)}")
    return "\n".join(output)

def main():
    choice = input("Enter '1' for console input or '2' for file input: ").strip()

    if choice == '1':
        input_line = input("Enter a line of code: ").strip()
    elif choice == '2':
        file_path = input("Enter file path: ").strip()
        try:
            with open(file_path, 'r') as file:
                input_line = file.read().strip()
        except FileNotFoundError:
            print("File not found.")
            return
    else:
        print("Invalid choice.")
        return

    classified_tokens = classify_tokens(input_line)
    result = format_output(classified_tokens)
    print("\nOutput:")
    print(result)

if __name__ == "__main__":
    main()

# file path : text.txt