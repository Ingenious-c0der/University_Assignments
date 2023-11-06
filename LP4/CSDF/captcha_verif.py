from PIL import Image, ImageDraw, ImageFont
from cv2 import imshow, imread
from captcha.image import ImageCaptcha
import random

# Generate a random CAPTCHA string
def generate_captcha_text():
    characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'
    captcha_text = ''.join(random.choice(characters) for _ in range(6))  # 6 characters in the CAPTCHA
    return captcha_text

# Generate and save a CAPTCHA image
def generate_captcha_image():
    captcha_text = generate_captcha_text()
    image = ImageCaptcha()
    data = image.generate(captcha_text)
    image.write(captcha_text, 'captcha.png')  # Save the image to 'captcha.png'

    return captcha_text

# Verify user input against the CAPTCHA text
def verify_captcha(input_text, captcha_text):
    return input_text == captcha_text

# Main program
if __name__ == "__main__":
    # Generate a CAPTCHA image
    captcha_text = generate_captcha_image()
    print(captcha_text)
    # Simulate user input (replace this with actual user input)
    user_input = input("Enter the CAPTCHA: ")

    # Verify the user input
    if verify_captcha(user_input, captcha_text):
        print("CAPTCHA verification successful.")
    else:
        print("CAPTCHA verification failed.")