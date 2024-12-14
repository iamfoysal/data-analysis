import java.io.*;
import java.util.*;
import java.util.regex.*;

public class LexicalAnalyzer {

    // Function to classify tokens
    public static Map<String, List<String>> classifyTokens(String inputLine) {
        // Define token categories
        Set<String> keywords = new HashSet<>(Arrays.asList("if", "else", "int", "float", "return", "for", "while", "do", "switch", "case"));
        Set<String> arithmeticOperators = new HashSet<>(Arrays.asList("+", "-", "*", "/", "="));
        Set<String> logicalOperators = new HashSet<>(Arrays.asList(">", ">=", "<", "<=", "==", "!="));
        Set<String> punctuation = new HashSet<>(Arrays.asList(";", ":", ","));
        Set<String> parentheses = new HashSet<>(Arrays.asList("(", ")", "{", "}", "[", "]"));

        // Regex patterns
        Pattern identifierPattern = Pattern.compile("^[a-zA-Z_][a-zA-Z0-9_]*$");
        Pattern constantPattern = Pattern.compile("^\\d+$");

        // Tokenize the input
        String[] tokens = inputLine.split("\\s+|(?=\\W)|(?<=\\W)");

        // Classify tokens
        Map<String, List<String>> classifiedTokens = new HashMap<>();

        for (String token : tokens) {
            if (keywords.contains(token)) {
                classifiedTokens.computeIfAbsent("Keyword", k -> new ArrayList<>()).add(token);
            } else if (arithmeticOperators.contains(token)) {
                classifiedTokens.computeIfAbsent("Arithmetic Operator", k -> new ArrayList<>()).add(token);
            } else if (logicalOperators.contains(token)) {
                classifiedTokens.computeIfAbsent("Logical Operator", k -> new ArrayList<>()).add(token);
            } else if (punctuation.contains(token)) {
                classifiedTokens.computeIfAbsent("Punctuation", k -> new ArrayList<>()).add(token);
            } else if (parentheses.contains(token)) {
                classifiedTokens.computeIfAbsent("Parenthesis", k -> new ArrayList<>()).add(token);
            } else if (constantPattern.matcher(token).matches()) {
                classifiedTokens.computeIfAbsent("Constant", k -> new ArrayList<>()).add(token);
            } else if (identifierPattern.matcher(token).matches()) {
                classifiedTokens.computeIfAbsent("Identifier", k -> new ArrayList<>()).add(token);
            } else {
                classifiedTokens.computeIfAbsent("Unknown", k -> new ArrayList<>()).add(token);
            }
        }

        return classifiedTokens;
    }

    // Function to format output
    public static void formatOutput(Map<String, List<String>> classifiedTokens) {
        for (Map.Entry<String, List<String>> entry : classifiedTokens.entrySet()) {
            String category = entry.getKey();
            List<String> tokens = entry.getValue();

            Set<String> uniqueTokens = new TreeSet<>(tokens);

            System.out.print(category + " (" + uniqueTokens.size() + "): ");
            System.out.println(String.join(", ", uniqueTokens));
        }
    }

    public static void main(String[] args) throws IOException {
        System.out.println("Enter '1' for console input or '2' for file input: ");
        Scanner scanner = new Scanner(System.in);
        int choice = scanner.nextInt();
        scanner.nextLine(); // Consume newline

        String inputLine = "";

        if (choice == 1) {
            System.out.println("Enter a line of code: ");
            inputLine = scanner.nextLine();
        } else if (choice == 2) {
            System.out.println("Enter file path: ");
            String filePath = scanner.nextLine();

            File file = new File(filePath);
            if (!file.exists()) {
                System.err.println("File not found.");
                return;
            }

            StringBuilder fileContent = new StringBuilder();
            try (BufferedReader br = new BufferedReader(new FileReader(file))) {
                String line;
                while ((line = br.readLine()) != null) {
                    fileContent.append(line).append("\n");
                }
            }
            inputLine = fileContent.toString().trim();
        } else {
            System.err.println("Invalid choice.");
            return;
        }

        Map<String, List<String>> classifiedTokens = classifyTokens(inputLine);
        System.out.println("\nOutput:");
        formatOutput(classifiedTokens);

        scanner.close();
    }
}
