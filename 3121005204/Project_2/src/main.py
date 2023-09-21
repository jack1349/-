import argparse
from fractions import Fraction
from GenerateQuestion import generate_question


def save_to_file(questions, answers, question_file, answer_file):
    with open(question_file, "w") as q_file:
        for question in questions:
            q_file.write(question + "\n")

    with open(answer_file, "w") as a_file:
        for answer in answers:
            a_file.write(str(answer) + "\n")


def main():
    parser = argparse.ArgumentParser(description="生成小学四则运算题目")
    parser.add_argument("-n", "--num_questions", type=int, default=10, help="要生成的题目数量")
    parser.add_argument("-r", "--range", type=int, default=10, help="随机数范围")
    parser.add_argument("-e", "--exercise_file", default=None, help="保存题目的文件名")
    parser.add_argument("-a", "--answer_file", default=None, help="保存答案的文件名")

    args = parser.parse_args()
    questions = []
    answers = []

    generated_questions = set()  # 用集合来存储已生成的题目，以检查重复

    for _ in range(args.num_questions):
        question, answer = generate_question(args, generated_questions)
        questions.append(question)
        answers.append(answer)

    save_to_file(questions, answers, "../file/Exercises.txt", "../file/Answers.txt")


if __name__ == "__main__":
    main()
