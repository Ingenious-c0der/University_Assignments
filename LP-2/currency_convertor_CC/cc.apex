public class CurrencyConversionController {
    public Decimal amount { get; set; }
    public String fromCurrency { get; set; }
    public String toCurrency { get; set; }
    public Decimal convertedAmount { get; set; }
    
    public List<SelectOption> getCurrencyOptions() {
        List<SelectOption> options = new List<SelectOption>();
        options.add(new SelectOption('USD', 'USD'));
        options.add(new SelectOption('EUR', 'EUR'));
        options.add(new SelectOption('GBP', 'GBP'));
        // Add more currency options as needed
        return options;
    }
    
    public void convertCurrency() {
        if (amount == null || fromCurrency == null || toCurrency == null) {
            ApexPages.addMessage(new ApexPages.Message(ApexPages.Severity.ERROR, 'Please provide all conversion details.'));
            return;
        }
        
        // Perform the currency conversion based on your exchange rates or an external API
        // Replace this logic with your actual currency conversion code
        if (fromCurrency == 'USD' && toCurrency == 'EUR') {
            convertedAmount = amount * 0.85;
        } else if (fromCurrency == 'USD' && toCurrency == 'GBP') {
            convertedAmount = amount * 0.72;
        } else {
            ApexPages.addMessage(new ApexPages.Message(ApexPages.Severity.ERROR, 'Exchange rate not available for specified currencies.'));
        }
    }
}