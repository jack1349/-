import random
from fractions import Fraction


def generate_operand(args):
    # 生成一个随机数，包括真分数的分子和分母
    operand = Fraction(random.randint(1, args.range), random.randint(1, args.range))
    return operand


def generate_expression(args):
    # 生成一个随机数作为第一个操作数
    expression = str(generate_operand(args))

    # 随机选择运算符数量，最多不超过3个
    num_operators = random.randint(1, 3)

    for _ in range(num_operators):
        # 随机选择运算符
        operator = random.choice(['+', '-', '*', '/'])

        # 生成下一个操作数
        operand = generate_operand(args)

        # 随机决定是否加括号
        if random.random() < 0.3:
            expression = f"({expression}) {operator} {operand}"
        else:
            expression = f"{expression} {operator} {operand}"

    return expression


def generate_question(args, generated_questions):
    while True:
        # 生成表达式
        expression = generate_expression(args)

        # 构建题目字符串
        question = f"{expression} = ?"

        # 如果题目已经生成过，重新生成
        if question not in generated_questions:
            generated_questions.add(question)  # 将生成的题目添加到集合中，以防重复
            break

    # 设置默认值
    answer = None

    try:
        # 计算答案
        answer = Fraction(eval(expression)).limit_denominator()
        if answer < 0:
            return generate_question(args, generated_questions)
        if answer.numerator > answer.denominator and answer.numerator % answer.denominator != 0:
            # 将分数转换为带分数的形式
            whole_part, fractional_part = divmod(answer.numerator, answer.denominator)

            # 将带分数格式化为字符串
            answer = f"{whole_part}'{fractional_part}/{answer.denominator}"
    except ZeroDivisionError:
        return generate_question(args, generated_questions)

    return question, answer
