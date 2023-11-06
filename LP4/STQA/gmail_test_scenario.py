import time
from selenium import webdriver

# Initialize the Selenium WebDriver (make sure to install the Selenium library and the appropriate webdriver)
driver = webdriver.Chrome()  # You can choose a different driver if needed (e.g., Firefox, Edge)

# Test Scenario: Gmail Login Page with Selenium Python

# Step 1: Open Gmail Login Page
driver.get("https://mail.google.com")

# Step 2: Verify Page Elements
# Check if the following elements are visible and functional
try:
    username_field = driver.find_element_by_id("identifierId")  # Username or Email field
    password_field = driver.find_element_by_name("password")  # Password field
    next_button = driver.find_element_by_id("identifierNext")  # "Next" button
    sign_in_button = driver.find_element_by_id("passwordNext")  # "Sign in" button
    forgot_email_link = driver.find_element_by_partial_link_text("Forgot email?")  # "Forgot email?" link
    forgot_password_link = driver.find_element_by_partial_link_text("Forgot password?")  # "Forgot password?" link
    create_account_link = driver.find_element_by_partial_link_text("Create account")  # "Create account" link
    help_link = driver.find_element_by_partial_link_text("Help")  # "Help" link
    google_logo = driver.find_element_by_id("logo")  # Google logo
    stay_signed_in_checkbox = driver.find_element_by_id("persistent")

    # Ensure the page layout and design are consistent
    assert username_field.is_displayed()
    assert password_field.is_displayed()
    assert next_button.is_displayed()
    assert sign_in_button.is_displayed()
    assert forgot_email_link.is_displayed()
    assert forgot_password_link.is_displayed()
    assert create_account_link.is_displayed()
    assert help_link.is_displayed()
    assert google_logo.is_displayed()
    assert stay_signed_in_checkbox.is_displayed()

    print("Step 2: Page Elements verification passed.")
except Exception as e:
    print("Step 2: Page Elements verification failed. Error:", str(e))

# Step 3: Valid Username and Password
username_field.send_keys("your_username@gmail.com")  # Replace with a valid Gmail username
next_button.click()
time.sleep(2)  # Wait for the next page to load
password_field = driver.find_element_by_name("password")  # Re-locate the password field after navigating
password_field.send_keys("your_password")  # Replace with a valid Gmail password
sign_in_button.click()

# Verify that the user is successfully logged into their Gmail account
try:
    inbox_title = driver.title
    assert "Inbox" in inbox_title
    print("Step 3: Successful login verified.")
except Exception as e:
    print("Step 3: Login verification failed. Error:", str(e))

# Step 4: Close the browser
driver.close()
