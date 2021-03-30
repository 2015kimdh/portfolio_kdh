# 초기 화면을 담당하는 곳임
from tkinter import *
from tkinter import font
from tkinter import messagebox


class MainFrame:
    def InitRenderText(self):
        # 데이터들을 출력하는 함수

        # 스크롤바 만들기
        self.RenderTextScrollbar = Scrollbar(self.frame)
        self.RenderTextScrollbar.place(x=self.width * 0.91, y=self.height / 30, height=self.height / 10 * 6)

        # 데이터 출력창 만들기
        self.RenderText = Text(self.frame, width=70, height=35, borderwidth=12, relief='ridge',
                               yscrollcommand=self.RenderTextScrollbar.set)

        # 이 j는 데이터들 번호 매길 때 사용할 것
        # [j] .... ---> [1], [2], [3] ....
        j = 0

        # 데이터를 출력하는 핵심 부분
        for i in self.dataList:
            self.RenderText.insert(INSERT, "[")
            self.RenderText.insert(INSERT, j + 1)
            self.RenderText.insert(INSERT, "] ")
            self.RenderText.insert(INSERT, "시설명: ")
            if i[0] is not None:
                self.RenderText.insert(INSERT, i[0])
            self.RenderText.insert(INSERT, "\n")

            if i[1] is not None:
                self.RenderText.insert(INSERT, "도로명주소: ")
                self.RenderText.insert(INSERT, i[1])
                self.RenderText.insert(INSERT, "\n\n")
            else:
                self.RenderText.insert(INSERT, "지번주소: ")
                self.RenderText.insert(INSERT, i[2])
                self.RenderText.insert(INSERT, "\n\n")
            j += 1

        # 출력 창 위치 시키고 스크롤바를 붙여둠
        self.RenderText.place(x=self.width/20, y=self.height/30)
        self.RenderTextScrollbar.config(command=self.RenderText.yview)

        # Text 객체를 disabled 로 선언해야 수정할 수 없음
        self.RenderText.configure(state='disabled')

    def SetData(self, CurFrame, DataList=None):
        # 혹시 몰라서 넣어둠... 쓸 일이 있으려나?
        if DataList is not None:
            self.dataList = DataList

        self.nextFrame = CurFrame

    def GetData(self):
        # 혹시 몰라서 넣어둠... 쓸 일이 있으려나? ... (2)
        return self.dataList

    def InitTopText(self):
        # 텍스트 라벨들을 한 곳에 모아뒀음

        # 상단에 앱 정보를 띄워주는 라벨
        self.mainText = Label(self.frame, font=self.TempFont, text="경기도 위치 패스트푸드점 검색기능을 제공")
        self.mainText.place(x=self.width * 0.2, y=self.height * 0.65)

        # 입력 라벨들인데 엔트리 옆에 있는 메시지 문장
        self.sigunText = Label(self.frame, font=self.TempFont, text="시ㆍ군")
        self.sigunText.place(x=self.width * 0.03, y=self.height / 10 * 7.2)

        self.dongText = Label(self.frame, font=self.TempFont, text="동 단위")
        self.dongText.place(x=self.width * 0.03, y=self.height / 10 * 8.2)

    def InitSearchEntry(self):
        # 대망의 입력 엔트리들

        # 시·군 입력 엔트리
        self.sigunEntry = Entry(self.frame, font=self.TempFont, width=45, borderwidth=12, relief='ridge')
        self.sigunEntry.place(x=self.width * 0.2, y=self.height / 10 * 7)

        # 동 단위 입력 엔트리
        self.dongEntry = Entry(self.frame, font=self.TempFont, width=45, borderwidth=12, relief='ridge')
        self.dongEntry.place(x=self.width * 0.2, y=self.height / 10 * 8)

    def SearchButtonAction(self):
        # 검색 버튼 눌렸을 때 xml 파싱하는 거임
        # 여긴 손 댄게 거의 없음

        import http.client
        import urllib

        conn = http.client.HTTPSConnection("openapi.gg.go.kr")
        hangul_utf8 = urllib.parse.quote(str(self.sigunEntry.get()))
        conn.request("GET",
                     "/Resrestrtfastfood?KEY=fead735fe2264921943cc45687420e65&pSize=1000&SIGUN_NM=" + hangul_utf8)
        req = conn.getresponse()

        self.dataList.clear()
        self.RenderText.configure(state='normal')

        if req.status == 200:
            Doc = req.read().decode('utf-8')
        if Doc is None:
            print("에러")
        else:
            from xml.etree import ElementTree
            tree = ElementTree.fromstring(Doc)

            itemElements = tree.getiterator("row")

            if self.dongEntry.get() == "":
                for row in itemElements:
                    name = row.find("BIZPLC_NM")
                    status = row.find("BSN_STATE_NM")
                    addr = row.find("REFINE_ROADNM_ADDR")
                    addr2 = row.find("REFINE_LOTNO_ADDR")
                    wido = row.find("REFINE_WGS84_LAT")
                    gyungdo = row.find("REFINE_WGS84_LOGT")

                    if status.text == "운영중":
                        self.dataList.append((name.text, addr.text, addr2.text, wido.text, gyungdo.text))
            else:
                for row in itemElements:
                    name = row.find("BIZPLC_NM")
                    status = row.find("BSN_STATE_NM")
                    addr = row.find("REFINE_ROADNM_ADDR")
                    addr2 = row.find("REFINE_LOTNO_ADDR")
                    wido = row.find("REFINE_WGS84_LAT")
                    gyungdo = row.find("REFINE_WGS84_LOGT")

                    if status.text == "운영중":
                        if addr.text is not None:
                            if self.dongEntry.get() in addr.text:
                                self.dataList.append((name.text, addr.text, addr2.text, wido.text, gyungdo.text))

            # 버튼을 눌렀을 때 출력 창에 있는 놈들 갱신하고 싶은데
            # 복잡하게 하기 귀찮아서 그냥 출력 함수 한 번 더 호출함
            self.InitRenderText()

    def InitSearchButton(self):
        # 검색 버튼을 만듦
        # self.SearchButton 이 변수 쓸일 있을까..
        Button(self.frame, font=self.TempFont, text="확 인", command=self.SearchButtonAction).place(
            x=self.width * 0.8, y=self.height / 10 * 9)

        # 이 밑에 부분은 내가 잠시 주석처리 함
        # Search1Button = Button(g_Tk, font=TempFont, text="갱 신", command=WizetClear)
        # Search1Button.pack()
        # Search1Button.place(x=w * 0.2, y=h / 10 * 9)

    def NextButtonAction(self):
        pass
        #self.nextFrame.Tkraise()


    def InitNextButton(self):
        Button(self.frame, font=self.TempFont, text="다 음", command=self.NextButtonAction).place(
            x=self.width - (self.width * 0.8), y=self.height / 10 * 9)


    def __init__(self, window, w, h):
        # 이 프레임 크기를 main에서 만드는 윈도우랑 일치시키기 위해
        self.width = w
        self.height = h

        self.frame = Frame(window, width=self.width, height=self.height)  # window 에 초기화면 frame을 생성한다.
        self.frame.pack()

        self.TempFont = font.Font(size=12, weight='bold', family='Consolas') # 여기저기서 쓸 폰트. 맘에 안 들면 바꿔라

        # 당장은 안 쓰지만 이따가 필요한 것들
        # 프레임 전환 버튼 만들기(test)
        self.nextButton = None
        self.nextFrame = None

        # 텍스트를 쓰는 라벨들
        self.mainText = None
        self.sigunText = None
        self.dongText = None

        # 엔트리
        self.sigunEntry = None
        self.dongEntry = None

        # 버튼
        self.SearchButton = None

        # 데이터들을 담는 리스트 ... 중요함!
        self.dataList = []

        # 출력하는 데 필요한 것들..
        self.RenderTextScrollbar = None
        self.RenderText = None

        # 꼭 실행해야 하는 함수들을 모아뒀음
        # Init 로 시작하는 애들만 호출하면 된다
        # why? -> 이 클래스를 만들자마자 필요한 것들이라
        self.InitTopText()
        self.InitSearchEntry()
        self.InitSearchButton()
        self.InitRenderText()
        self.InitNextButton()

class SecondFrame:
    def InitRenderText(self):
        # 데이터들을 출력하는 함수

        # 스크롤바 만들기
        self.RenderTextScrollbar = Scrollbar(self.frame)
        self.RenderTextScrollbar.place(x=self.width * 0.91, y=self.height / 30, height=self.height / 10 * 6)

        # 데이터 출력창 만들기
        self.RenderText = Text(self.frame, width=70, height=35, borderwidth=12, relief='ridge',
                               yscrollcommand=self.RenderTextScrollbar.set)

        # 이 j는 데이터들 번호 매길 때 사용할 것
        # [j] .... ---> [1], [2], [3] ....
        j = 0

        # 데이터를 출력하는 핵심 부분
        for i in self.dataList:
            self.RenderText.insert(INSERT, "[")
            self.RenderText.insert(INSERT, j + 1)
            self.RenderText.insert(INSERT, "] ")
            self.RenderText.insert(INSERT, "시설명: ")
            if i[0] is not None:
                self.RenderText.insert(INSERT, i[0])
            self.RenderText.insert(INSERT, "\n")

            if i[1] is not None:
                self.RenderText.insert(INSERT, "도로명주소: ")
                self.RenderText.insert(INSERT, i[1])
                self.RenderText.insert(INSERT, "\n\n")
            else:
                self.RenderText.insert(INSERT, "지번주소: ")
                self.RenderText.insert(INSERT, i[2])
                self.RenderText.insert(INSERT, "\n\n")
            j += 1

        # 출력 창 위치 시키고 스크롤바를 붙여둠
        self.RenderText.place(x=self.width/20, y=self.height/30)
        self.RenderTextScrollbar.config(command=self.RenderText.yview)

        # Text 객체를 disabled 로 선언해야 수정할 수 없음
        self.RenderText.configure(state='disabled')

    def __init__(self, window, w, h):
        self.width = w
        self.height = h

        self.frame = Frame(window, width=w, height=h)
        self.frame.pack()
        self.mainText = Label(self.frame,  text="아아아아아아아아아ㅏ아아아아아ㅏ가")
        self.mainText.place(x=self.width * 0.2, y=self.height * 0.65)


        #self.InitRenderText()

