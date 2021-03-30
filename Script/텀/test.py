from tkinter import *
import tkinter.messagebox


class TickTacToe:

    def pressed(self, Row, Col):
        for r in range(5, -1, -1): # r = 5 , 4, 3 , 2 , 1
            if self.buttonList[r * 7 + Col]['text'] == ' ':
                if self.turn:   # o 차례
                    self.buttonList[r * 7 + Col].configure(text="O", image=self.imageList[0])
                    self.board[r * 7 + Col] = "O"
                else:           # x 차례
                    self.buttonList[r * 7 + Col].configure(text="X", image=self.imageList[1])
                    self.board[r * 7 + Col] = "X"
                self.turn = not self.turn
                break

        self.endGame()

    def MBox(self,txt):
        if txt == 'O':
            tkinter.messagebox.showinfo("승리", "O 승리!")
        elif txt == 'X':
            tkinter.messagebox.showinfo("승리", "X 승리!")
        else:
            tkinter.messagebox.showinfo("비김", "비겼습니다!")
        self.again()


    def endGame(self):
        for i in range(6):
            for j in range(4):
                if self.board[i * 7 + j] != ' ':
                        if self.board[i * 7 + j] == self.board[i * 7 + j + 1] == self.board[i * 7 + j + 2] == self.board[i * 7 + j + 3]:
                            self.buttonList[i * 7 + j].configure(relief="solid")
                            self.buttonList[i * 7 + j + 1].configure(relief="solid")
                            self.buttonList[i * 7 + j + 2].configure(relief="solid")
                            self.buttonList[i * 7 + j + 3].configure(relief="solid")
                            self.MBox(self.board[i * 7 + j])

        for i in range(3):
            for j in range(7):
                if self.board[7 * i + j] != ' ':
                    if self.board[7 * i + j] == self.board[7*(i+1) + j] == self.board[7*(i+2) + j] == self.board[7*(i+3) + j]:
                        self.buttonList[7 * i + j].configure(relief="solid")
                        self.buttonList[7*(i+1) + j].configure(relief="solid")
                        self.buttonList[7*(i+2) + j].configure(relief="solid")
                        self.buttonList[7*(i+3) + j].configure(relief="solid")
                        self.MBox(self.board[7 * i + j])

        for i in range(3):
            for j in range(4):
                if self.board[7 * i + j] != ' ':
                    if self.board[7 * i + j] == self.board[7*(i+1) + j+1] == self.board[7*(i+2) + j+2] == self.board[7*(i+3) + j+3]:
                        self.buttonList[7 * i + j].configure(relief="solid")
                        self.buttonList[7 * (i+1) + j+1].configure(relief="solid")
                        self.buttonList[7 * (i+2) + j+2].configure(relief="solid")
                        self.buttonList[7 * (i+3) + j+3].configure(relief="solid")
                        self.MBox(self.board[7 * i + j])

        for i in range(3):
            for j in range(6, 2, -1):
                if self.board[7*i + j] != ' ':
                    if self.board[7 * i + j] == self.board[7*(i+1) + j-1] == self.board[7*(i+2) + j-2] == self.board[7*(i+3) + j-3]:
                        self.buttonList[7*i + j].configure(relief="solid")
                        self.buttonList[7*(i+1) + j-1].configure(relief="solid")
                        self.buttonList[7*(i+2) + j-2].configure(relief="solid")
                        self.buttonList[7*(i+3) + j-3].configure(relief="solid")
                        self.MBox(self.board[i * 7 + j])

        if not ' ' in self.board:
            for r in range(6):
                for c in range(7):
                    self.buttonList[r * 7 + c].configure(relief='solid')
            self.MBox(' ')


    def again(self):
        for r in range(6):
            for c in range(7):
                self.buttonList[r*7+c].configure(text=' ', image=self.imageList[2], relief="flat")
                self.board[r*7+c] = ' '
                self.turn = True


    def __init__(self):
        window = Tk()
        window.title("사목게임")
        self.imageList = []
        self.turn = True
        self.imageList.append(PhotoImage(file="D:/스크립트\pybook\image/o.gif"))
        self.imageList.append(PhotoImage(file="D:/스크립트\pybook\image/x.gif"))
        self.imageList.append(PhotoImage(file="D:/스크립트\pybook\image/empty.gif"))
        self.buttonList = []
        self.board = []
        frame1 = Frame(window)
        frame1.pack()
        for r in range(6):
            for c in range(7):
                self.board.append(' ')
                self.buttonList.append(Button(frame1, relief='flat', text=" ", image=self.imageList[2],
                                              command=lambda Row = r, Col = c:self.pressed(Row, Col)))
                self.buttonList[r*7+c].grid(row=r, column=c)
        frame2 = Frame(window)
        frame2.pack()
        Button(frame2, text="다시하기", command=self.again).pack()

        window.mainloop()

TickTacToe()