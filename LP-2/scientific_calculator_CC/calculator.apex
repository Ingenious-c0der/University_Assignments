public class ScientificCalculatorController {
    public Decimal inputNumber { get; set; }
    public Decimal displayValue { get; set; }
    
    public void clear() {
        inputNumber = null;
        displayValue = null;
    }
    
    public void calculateSquareRoot() {
        if (inputNumber != null) {
            displayValue = Math.sqrt(inputNumber);
        }
    }
    
    public void calculateSquare() {
        if (inputNumber != null) {
            displayValue = inputNumber * inputNumber;
        }
    }
    
    public void calculateInverse() {
        if (inputNumber != null && inputNumber != 0) {
            displayValue = 1 / inputNumber;
        }
    }
    
    public void calculatePercentage() {
        if (inputNumber != null) {
            displayValue = inputNumber / 100;
        }
    }
    
    public void calculateSin() {
        if (inputNumber != null) {
            displayValue = Math.sin(inputNumber);
        }
    }
    
    public void calculateCos() {
        if (inputNumber != null) {
            displayValue = Math.cos(inputNumber);
        }
    }
    
    public void calculateTan() {
        if (inputNumber != null) {
            displayValue = Math.tan(inputNumber);
        }
    }
    
    public void calculateLog() {
        if (inputNumber != null && inputNumber > 0) {
            displayValue = Math.log10(inputNumber);
        }
    }
}