import java.util.*;

class Sum {
    public static void main(String[] args) {
        int a,b,sum;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter first number");
        a = scanner.nextInt();
        System.out.println("Enter second number");
        b = scanner.nextInt();
        sum = a+b; 
        System.out.println("Hello, World!" + sum); 
        scanner.close();
    }
}