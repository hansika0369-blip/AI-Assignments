import random
import string

def generate_captcha(length=6):
    letters_and_digits = string.ascii_letters + string.digits
    captcha = ''.join(random.choice(letters_and_digits) for i in range(length))
    return captcha

def captcha_test():
    captcha = generate_captcha()
    print("CAPTCHA:", captcha)
    user_input = input("Enter CAPTCHA: ")
    if user_input == captcha:
        print("CAPTCHA passed! You are human.")
    else:
        print("CAPTCHA failed! Try again.")

captcha_test()