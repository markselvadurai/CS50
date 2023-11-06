import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from time import gmtime, strftime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    userid = session["user_id"]
    symbol = db.execute("select symbol from owned where user_id = ?", userid)
    shares = db.execute("select shares from owned where user_id = ?", userid)
    price = []
    for i in range(len(symbol)):
        price.append( float(lookup(symbol[i]["symbol"])["price"]))
    length = len(symbol)
    print(price)
    bank = db.execute("select cash from users where id = ?",session["user_id"])
    bank = round(bank[0]["cash"],2)
    full = 0
    for i in range(len(price)):
        print(price[i])
        full += price[i] * shares[i]["shares"]

    for i in range(len(shares)):
        if shares[i]["shares"] == 0:
            db.execute("delete from owned where user_id = ? and symbol = ?",userid,symbol[i]["symbol"])

    return render_template("index.html",symbol = symbol, shares = shares, price = price, len = length, bank = bank, full = full)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    else:
        try:
            symbol = request.form.get("symbol")
            shares = float(request.form.get("shares"))
            price = float(lookup(symbol)["price"])
            if not price:
                apology("Invalid Symbol")
            elif not symbol:
                apology("Enter Symbol")
            elif shares <= 0:
                apology("Enter Shares")
            date = strftime("%Y-%m-%d %H:%M:%S", gmtime())
            bank = db.execute("select cash from users where id = ?",session["user_id"])
            print(price*shares)
            if (price*shares) <= float(bank[0]["cash"]):
                db.execute("update users set cash = ? where id = ?", float(bank[0]["cash"])-(price*shares),session["user_id"])
                db.execute("insert into history (user_id,price,symbol,shares,type,date) values (?,?,?,?,?,?)", session["user_id"], price, symbol, shares,"buy",date)
                if (db.execute("select * from owned where user_id = ? and symbol = ?", session["user_id"], symbol)):
                    db.execute("update owned set shares = shares + ? where user_id = ? and symbol = ?", shares, session["user_id"], symbol)
                else:
                    db.execute("insert into owned (user_id, symbol, shares) values (?,?,?)",session["user_id"], symbol, shares)
            else:
                return apology("Not enough money")
        except:
            return apology("invald input")


        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    userid = session["user_id"]
    data = db.execute("select * from history where user_id = ? order by date asc",userid)
    length = len(data)
    return render_template("history.html",data=data,len=length)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        try:
            symbol = request.form.get("symbol")
            name =  lookup(symbol)["name"]
            price = lookup(symbol)["price"]
            symbol = lookup(symbol)["symbol"]
            if not symbol:
                return apology("Enter a symbol")
            elif not name:
                return apology("Invalid symbol")

            return render_template("quoted.html",name=name,price=price,symbol=symbol)
        except:
            return apology("Invalid")
    else:
        return render_template("quote.html")




@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirm = request.form.get("passwordc")

        if not username:
            return apology("must provide username", 403)

        elif not password:
            return apology("must provide password", 403)

        elif not confirm:
            return apology("must confirm password", 403)

        elif confirm != password:
            return apology("password is not matching confirmation", 403)

        elif (db.execute("select username from users where username = ?", username)):
            return apology("Name Taken")

        else:
            newp = generate_password_hash(password)

            db.execute("insert into users (username,hash) values (?,?)",username,newp)
            session["user_id"] = rows[0]["id"]
            return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        userid = session["user_id"]
        symbol = db.execute("select symbol from owned where user_id = ?", userid)
        return render_template("sell.html",symbol = symbol)
    else:
        userid = session["user_id"]
        symbolrd = request.form.get("symbol")
        sellam = int(request.form.get("shares"))
        sharetot = db.execute("select shares from owned where user_id = ? and symbol = ?", userid, symbolrd)
        sharetot = int(sharetot[0]["shares"])
        price = float(lookup(symbolrd)["price"])
        date = strftime("%Y-%m-%d %H:%M:%S", gmtime())
        if sellam <= 0 or sellam > sharetot:
            return apology("Invalid input")
        else:
            ret = round(sellam * price,2)
            db.execute("update owned set shares = shares - ? where user_id = ? and symbol = ?",sellam,userid,symbolrd)
            db.execute("update users set cash = cash + ? where id = ?", ret, userid)
            db.execute("insert into history (user_id,price,symbol,shares,type,date) values (?,?,?,?,?,?)",userid,ret,symbolrd,sellam,"sell",date)
            return redirect("/")



