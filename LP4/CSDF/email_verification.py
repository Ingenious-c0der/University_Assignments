import email
import os
import re
from datetime import datetime

# Function to extract and display email headers
def extract_email_headers(email_file):
    try:
        with open(email_file, 'rb') as file:
            msg = email.message_from_binary_file(file)

            # Extract and display common email headers
            print("From:", msg['From'])
            print("To:", msg['To'])
            print("Subject:", msg['Subject'])
            print("Date:", msg['Date'])
            print("Message-ID:", msg['Message-ID'])

            # Additional headers can be extracted as needed
            # Example: msg['Received'], msg['X-Mailer']

            # Check for future dates
            date_str = msg['Date']
            if date_str:
                email_date = datetime.strptime(date_str, '%a, %d %b %Y %H:%M:%S %z')
                current_date = datetime.now(email_date.tzinfo)
                if email_date > current_date:
                    print("WARNING: Email has a future date.")

            # Check for specific keywords in email content
            email_content = msg.get_payload()
            if email_content:
                keywords = ['phishing', 'scam']
                for keyword in keywords:
                    if re.search(keyword, email_content, re.I):
                        print(f"WARNING: Email content contains '{keyword}' keyword.")

    except Exception as e:
        print("An error occurred while processing the email:", e)

# Main program
if __name__ == '__main__':
    # Specify the path to the email file (in .eml format)
    email_file_path = 'test.eml'

    if os.path.exists(email_file_path):
        print("Email Header Information:")
        extract_email_headers(email_file_path)
    else:
        print("The specified email file does not exist.")