import random

responses = {
    "hi": ["Hello!", "Hi there!", "Hey!"],
    "how are you": ["I'm fine, thanks!", "Doing well, you?", "All good!"],
    "bye": ["Goodbye!", "See you later!", "Bye!"]
}

def chatbot():
    print("Chatbot: Hello! Try to see if I seem human.")
    while True:
        user_input = input("You: ").lower()
        if user_input in responses:
            print("Chatbot:", random.choice(responses[user_input]))
        else:
            print("Chatbot: Sorry, I didn't understand that.")
        if user_input == "bye":
            break

chatbot()