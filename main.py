import random
from math import ceil, log2
from flask import Flask, request, render_template, session

app = Flask(__name__)
app.secret_key = 'flask_secret'


@app.route('/', methods=['GET', 'POST'])
@app.route('/index', methods=['GET', 'POST'])
def index():
    info = {
        'min': 100,
        'max': 140,
    }
    info['total_attempts'] = ceil(log2(info['max'] - info['min'] + 1))

    if request.method == 'GET':
        session['pr_num'] = random.randint(info['min'], info['max'])
        session['attempts'] = info['total_attempts']
        info['attempts'] = info['total_attempts']
    elif request.method == 'POST':
        input_num = int(request.form.get('input-num'))
        session['attempts'] -= 1
        info['attempts'] = session['attempts']
        if input_num == session['pr_num']:
            info['disabled'] = 'disabled'
            info['game_info'] = 'You won!'
        elif session['attempts'] == 0:
            info['disabled'] = 'disabled'
            info['game_info'] = 'You lose'
        elif input_num < session['pr_num']:
            info['game_info'] = 'Guess number is more'
        elif input_num > session['pr_num']:
            info['game_info'] = 'Guess number is less'
        else:
            info['disabled'] = 'disabled'
            info['game_info'] = 'Error'
        info['out_num'] = session['pr_num']
    return render_template("index.html", **info)


if __name__ == "__main__":
    app.run(host='localhost', port=8000)
