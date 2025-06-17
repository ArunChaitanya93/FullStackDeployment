from flask import Flask, request, jsonify, render_template
import subprocess, json

app = Flask(__name__)  # looks in ./templates by default

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/api/multiply', methods=['POST'])
def multiply():
    data = request.get_json(force=True)
    try:
        # call the C++ CLI
        proc = subprocess.run(
            ['./matmul'],
            input=json.dumps(data),
            text=True,
            capture_output=True,
            check=True
        )
        return jsonify(json.loads(proc.stdout))
    except subprocess.CalledProcessError as e:
        # return any C++ errors
        return jsonify(error=e.stderr.strip() or "C++ error"), 500

if __name__ == '__main__':
    app.run(port=8080, debug=True)
