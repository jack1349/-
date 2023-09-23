from fractions import Fraction


def check_questions(args):
    questions = []
    answers = []
    correct = []
    wrong = []

    try:
        with open(args.exercise_file, "r") as q_file:
            for question in q_file:
                questions.append(question)
    except FileNotFoundError:
        print(f"Error: The file {args.exercise_file} was not found.")
        return None
    except Exception as e:
        print(f"An error occurred: {str(e)}")
        return None

    try:
        with open(args.answer_file, "r") as a_file:
            for answer in a_file:
                answer = answer.replace('\n', '')
                answers.append(str(answer))
    except FileNotFoundError:
        print(f"Error: The file {args.answer_file} was not found.")
        return None
    except Exception as e:
        print(f"An error occurred: {str(e)}")
        return None

    for index, question in enumerate(questions):
        try:
            # 计算答案
            answer = Fraction(eval(question)).limit_denominator()
            if answer.numerator > answer.denominator and answer.numerator % answer.denominator != 0:
                # 将分数转换为带分数的形式
                whole_part, fractional_part = divmod(answer.numerator, answer.denominator)

                # 将带分数格式化为字符串
                answer = f"{whole_part}'{fractional_part}/{answer.denominator}"

            if "'" not in str(answers[index]):
                answers[index] = Fraction(answers[index]).limit_denominator()
                if answers[index].numerator > answers[index].denominator \
                        and answers[index].numerator % answers[index].denominator != 0:
                    # 将分数转换为带分数的形式
                    whole_part, fractional_part = divmod(answers[index].numerator, answers[index].denominator)

                    # 将带分数格式化为字符串
                    answers[index] = f"{whole_part}'{fractional_part}/{answers[index].denominator}"

            if str(answer) == str(answers[index]):
                correct.append(index + 1)
            else:
                wrong.append(index + 1)
        except ZeroDivisionError:
            print(f'第{index + 1}题 error\n')
        except (SyntaxError, NameError):
            print(f"第{index + 1}题运算表达式错误\n")

    try:
        with open("../file/Grade.txt", "w") as a_file:
            result = f"Correct: {len(correct)} ({', '.join(str(num) for num in correct)})"
            a_file.write(str(result) + "\n")
            result = f"Wrong: {len(wrong)} ({', '.join(str(num) for num in wrong)})"
            a_file.write(str(result))
    except FileNotFoundError:
        print(f"Error: The file ../file/Grade.txt was not found.")
        return None
    except Exception as e:
        print(f"An error occurred: {str(e)}")
        return None
