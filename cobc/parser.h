/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    TOKEN_EOF = 0,                 /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    THREEDIMENSIONAL = 258,        /* "3D"  */
    ABSENT = 259,                  /* ABSENT  */
    ACCEPT = 260,                  /* ACCEPT  */
    ACCESS = 261,                  /* ACCESS  */
    ACTIVEX = 262,                 /* "ACTIVE-X"  */
    ACTION = 263,                  /* ACTION  */
    ACTUAL = 264,                  /* ACTUAL  */
    ADD = 265,                     /* ADD  */
    ADDRESS = 266,                 /* ADDRESS  */
    ADJUSTABLE_COLUMNS = 267,      /* "ADJUSTABLE-COLUMNS"  */
    ADVANCING = 268,               /* ADVANCING  */
    AFTER = 269,                   /* AFTER  */
    ALIGNMENT = 270,               /* ALIGNMENT  */
    ALL = 271,                     /* ALL  */
    ALLOCATE = 272,                /* ALLOCATE  */
    ALLOWING = 273,                /* ALLOWING  */
    ALPHABET = 274,                /* ALPHABET  */
    ALPHABETIC = 275,              /* ALPHABETIC  */
    ALPHABETIC_LOWER = 276,        /* "ALPHABETIC-LOWER"  */
    ALPHABETIC_UPPER = 277,        /* "ALPHABETIC-UPPER"  */
    ALPHANUMERIC = 278,            /* ALPHANUMERIC  */
    ALPHANUMERIC_EDITED = 279,     /* "ALPHANUMERIC-EDITED"  */
    ALSO = 280,                    /* ALSO  */
    ALTER = 281,                   /* ALTER  */
    ALTERNATE = 282,               /* ALTERNATE  */
    AND = 283,                     /* AND  */
    ANY = 284,                     /* ANY  */
    APPLY = 285,                   /* APPLY  */
    ARE = 286,                     /* ARE  */
    AREA = 287,                    /* AREA  */
    AREAS = 288,                   /* AREAS  */
    ARGUMENT_NUMBER = 289,         /* "ARGUMENT-NUMBER"  */
    ARGUMENT_VALUE = 290,          /* "ARGUMENT-VALUE"  */
    ARITHMETIC = 291,              /* ARITHMETIC  */
    AS = 292,                      /* AS  */
    ASCENDING = 293,               /* ASCENDING  */
    ASCII = 294,                   /* ASCII  */
    ASSIGN = 295,                  /* ASSIGN  */
    AT = 296,                      /* AT  */
    ATTRIBUTE = 297,               /* ATTRIBUTE  */
    ATTRIBUTES = 298,              /* ATTRIBUTES  */
    AUTO = 299,                    /* AUTO  */
    AUTO_DECIMAL = 300,            /* "AUTO-DECIMAL"  */
    AUTO_SPIN = 301,               /* "AUTO-SPIN"  */
    AUTOMATIC = 302,               /* AUTOMATIC  */
    AWAY_FROM_ZERO = 303,          /* "AWAY-FROM-ZERO"  */
    BACKGROUND_COLOR = 304,        /* "BACKGROUND-COLOR"  */
    BACKGROUND_HIGH = 305,         /* "BACKGROUND-HIGH"  */
    BACKGROUND_LOW = 306,          /* "BACKGROUND-LOW"  */
    BACKGROUND_STANDARD = 307,     /* "BACKGROUND-STANDARD"  */
    BAR = 308,                     /* BAR  */
    BASED = 309,                   /* BASED  */
    BEFORE = 310,                  /* BEFORE  */
    BELL = 311,                    /* BELL  */
    BINARY = 312,                  /* BINARY  */
    BINARY_C_LONG = 313,           /* "BINARY-C-LONG"  */
    BINARY_CHAR = 314,             /* "BINARY-CHAR"  */
    BINARY_DOUBLE = 315,           /* "BINARY-DOUBLE"  */
    BINARY_LONG = 316,             /* "BINARY-LONG"  */
    BINARY_SEQUENTIAL = 317,       /* "BINARY-SEQUENTIAL"  */
    BINARY_SHORT = 318,            /* "BINARY-SHORT"  */
    BIT = 319,                     /* BIT  */
    BITMAP = 320,                  /* BITMAP  */
    BITMAP_END = 321,              /* "BITMAP-END"  */
    BITMAP_HANDLE = 322,           /* "BITMAP-HANDLE"  */
    BITMAP_NUMBER = 323,           /* "BITMAP-NUMBER"  */
    BITMAP_START = 324,            /* "BITMAP-START"  */
    BITMAP_TIMER = 325,            /* "BITMAP-TIMER"  */
    BITMAP_TRAILING = 326,         /* "BITMAP-TRAILING"  */
    BITMAP_TRANSPARENT_COLOR = 327, /* "BITMAP-TRANSPARENT-COLOR"  */
    BITMAP_WIDTH = 328,            /* "BITMAP-WIDTH"  */
    BLANK = 329,                   /* BLANK  */
    BLINK = 330,                   /* BLINK  */
    BLOCK = 331,                   /* BLOCK  */
    BOTTOM = 332,                  /* BOTTOM  */
    BOX = 333,                     /* BOX  */
    BOXED = 334,                   /* BOXED  */
    BULK_ADDITION = 335,           /* "BULK-ADDITION"  */
    BUSY = 336,                    /* BUSY  */
    BUTTONS = 337,                 /* BUTTONS  */
    BY = 338,                      /* BY  */
    BYTE_LENGTH = 339,             /* "BYTE-LENGTH"  */
    C = 340,                       /* C  */
    CALENDAR_FONT = 341,           /* "CALENDAR-FONT"  */
    CALL = 342,                    /* CALL  */
    CANCEL = 343,                  /* CANCEL  */
    CANCEL_BUTTON = 344,           /* "CANCEL-BUTTON"  */
    CAPACITY = 345,                /* CAPACITY  */
    CARD_PUNCH = 346,              /* "CARD-PUNCH"  */
    CARD_READER = 347,             /* "CARD-READER"  */
    CASSETTE = 348,                /* CASSETTE  */
    CCOL = 349,                    /* CCOL  */
    CD = 350,                      /* CD  */
    CELL = 351,                    /* CELL  */
    CELL_COLOR = 352,              /* "CELL-COLOR"  */
    CELL_DATA = 353,               /* "CELL-DATA"  */
    CELL_FONT = 354,               /* "CELL-FONT"  */
    CELL_PROTECTION = 355,         /* "CELL-PROTECTION"  */
    CENTER = 356,                  /* CENTER  */
    CENTERED = 357,                /* CENTERED  */
    CENTERED_HEADINGS = 358,       /* "CENTERED-HEADINGS"  */
    CENTURY_DATE = 359,            /* "CENTURY-DATE"  */
    CF = 360,                      /* CF  */
    CH = 361,                      /* CH  */
    CHAINING = 362,                /* CHAINING  */
    CHANGED = 363,                 /* CHANGED  */
    CHARACTER = 364,               /* CHARACTER  */
    CHARACTERS = 365,              /* CHARACTERS  */
    CHECK_BOX = 366,               /* "CHECK-BOX"  */
    CLASS = 367,                   /* CLASS  */
    CLASSIFICATION = 368,          /* CLASSIFICATION  */
    CLASS_NAME = 369,              /* "class-name"  */
    CLEAR_SELECTION = 370,         /* "CLEAR-SELECTION"  */
    CLINE = 371,                   /* CLINE  */
    CLINES = 372,                  /* CLINES  */
    CLOSE = 373,                   /* CLOSE  */
    COBOL = 374,                   /* COBOL  */
    CODE = 375,                    /* CODE  */
    CODE_SET = 376,                /* "CODE-SET"  */
    COLLATING = 377,               /* COLLATING  */
    COL = 378,                     /* COL  */
    COLOR = 379,                   /* COLOR  */
    COLORS = 380,                  /* COLORS  */
    COLS = 381,                    /* COLS  */
    COLUMN = 382,                  /* COLUMN  */
    COLUMN_COLOR = 383,            /* "COLUMN-COLOR"  */
    COLUMN_DIVIDERS = 384,         /* "COLUMN-DIVIDERS"  */
    COLUMN_FONT = 385,             /* "COLUMN-FONT"  */
    COLUMN_HEADINGS = 386,         /* "COLUMN-HEADINGS"  */
    COLUMN_PROTECTION = 387,       /* "COLUMN-PROTECTION"  */
    COLUMNS = 388,                 /* COLUMNS  */
    COMBO_BOX = 389,               /* "COMBO-BOX"  */
    COMMA = 390,                   /* COMMA  */
    COMMAND_LINE = 391,            /* "COMMAND-LINE"  */
    COMMA_DELIM = 392,             /* "comma delimiter"  */
    COMMIT = 393,                  /* COMMIT  */
    COMMON = 394,                  /* COMMON  */
    COMMUNICATION = 395,           /* COMMUNICATION  */
    COMP = 396,                    /* COMP  */
    COMPUTE = 397,                 /* COMPUTE  */
    COMP_0 = 398,                  /* "COMP-0"  */
    COMP_1 = 399,                  /* "COMP-1"  */
    COMP_2 = 400,                  /* "COMP-2"  */
    COMP_3 = 401,                  /* "COMP-3"  */
    COMP_4 = 402,                  /* "COMP-4"  */
    COMP_5 = 403,                  /* "COMP-5"  */
    COMP_6 = 404,                  /* "COMP-6"  */
    COMP_N = 405,                  /* "COMP-N"  */
    COMP_X = 406,                  /* "COMP-X"  */
    CONCATENATE_FUNC = 407,        /* "FUNCTION CONCATENATE"  */
    CONDITION = 408,               /* CONDITION  */
    CONFIGURATION = 409,           /* CONFIGURATION  */
    CONSTANT = 410,                /* CONSTANT  */
    CONTAINS = 411,                /* CONTAINS  */
    CONTENT = 412,                 /* CONTENT  */
    CONTENT_LENGTH_FUNC = 413,     /* "FUNCTION CONTENT-LENGTH"  */
    CONTENT_OF_FUNC = 414,         /* "FUNCTION CONTENT-OF"  */
    CONTINUE = 415,                /* CONTINUE  */
    CONTROL = 416,                 /* CONTROL  */
    CONTROLS = 417,                /* CONTROLS  */
    CONVERSION = 418,              /* CONVERSION  */
    CONVERTING = 419,              /* CONVERTING  */
    COPY = 420,                    /* COPY  */
    COPY_SELECTION = 421,          /* "COPY-SELECTION"  */
    CORE_INDEX = 422,              /* "CORE-INDEX"  */
    CORRESPONDING = 423,           /* CORRESPONDING  */
    COUNT = 424,                   /* COUNT  */
    CRT = 425,                     /* CRT  */
    CRT_UNDER = 426,               /* "CRT-UNDER"  */
    CSIZE = 427,                   /* CSIZE  */
    CURRENCY = 428,                /* CURRENCY  */
    CURRENT_DATE_FUNC = 429,       /* "FUNCTION CURRENT-DATE"  */
    CURSOR = 430,                  /* CURSOR  */
    CURSOR_COL = 431,              /* "CURSOR-COL"  */
    CURSOR_COLOR = 432,            /* "CURSOR-COLOR"  */
    CURSOR_FRAME_WIDTH = 433,      /* "CURSOR-FRAME-WIDTH"  */
    CURSOR_ROW = 434,              /* "CURSOR-ROW"  */
    CURSOR_X = 435,                /* "CURSOR-X"  */
    CURSOR_Y = 436,                /* "CURSOR-Y"  */
    CUSTOM_PRINT_TEMPLATE = 437,   /* "CUSTOM-PRINT-TEMPLATE"  */
    CYCLE = 438,                   /* CYCLE  */
    CYL_INDEX = 439,               /* "CYL-INDEX"  */
    CYL_OVERFLOW = 440,            /* "CYL-OVERFLOW"  */
    DASHED = 441,                  /* DASHED  */
    DATA = 442,                    /* DATA  */
    DATA_COLUMNS = 443,            /* "DATA-COLUMNS"  */
    DATA_TYPES = 444,              /* "DATA-TYPES"  */
    DATE = 445,                    /* DATE  */
    DATE_ENTRY = 446,              /* "DATE-ENTRY"  */
    DAY = 447,                     /* DAY  */
    DAY_OF_WEEK = 448,             /* "DAY-OF-WEEK"  */
    DE = 449,                      /* DE  */
    DEBUGGING = 450,               /* DEBUGGING  */
    DECIMAL_POINT = 451,           /* "DECIMAL-POINT"  */
    DECLARATIVES = 452,            /* DECLARATIVES  */
    DEFAULT = 453,                 /* DEFAULT  */
    DEFAULT_BUTTON = 454,          /* "DEFAULT-BUTTON"  */
    DEFAULT_FONT = 455,            /* "DEFAULT-FONT"  */
    DELETE = 456,                  /* DELETE  */
    DELIMITED = 457,               /* DELIMITED  */
    DELIMITER = 458,               /* DELIMITER  */
    DEPENDING = 459,               /* DEPENDING  */
    DESCENDING = 460,              /* DESCENDING  */
    DESTINATION = 461,             /* DESTINATION  */
    DESTROY = 462,                 /* DESTROY  */
    DETAIL = 463,                  /* DETAIL  */
    DISABLE = 464,                 /* DISABLE  */
    DISC = 465,                    /* DISC  */
    DISK = 466,                    /* DISK  */
    DISP = 467,                    /* DISP  */
    DISPLAY = 468,                 /* DISPLAY  */
    DISPLAY_COLUMNS = 469,         /* "DISPLAY-COLUMNS"  */
    DISPLAY_FORMAT = 470,          /* "DISPLAY-FORMAT"  */
    DISPLAY_OF_FUNC = 471,         /* "FUNCTION DISPLAY-OF"  */
    DIVIDE = 472,                  /* DIVIDE  */
    DIVIDERS = 473,                /* DIVIDERS  */
    DIVIDER_COLOR = 474,           /* "DIVIDER-COLOR"  */
    DIVISION = 475,                /* DIVISION  */
    DOTDASH = 476,                 /* DOTDASH  */
    DOTTED = 477,                  /* DOTTED  */
    DRAG_COLOR = 478,              /* "DRAG-COLOR"  */
    DROP_DOWN = 479,               /* "DROP-DOWN"  */
    DROP_LIST = 480,               /* "DROP-LIST"  */
    DOWN = 481,                    /* DOWN  */
    DUPLICATES = 482,              /* DUPLICATES  */
    DYNAMIC = 483,                 /* DYNAMIC  */
    EBCDIC = 484,                  /* EBCDIC  */
    EC = 485,                      /* EC  */
    ECHO = 486,                    /* ECHO  */
    EGI = 487,                     /* EGI  */
    EIGHTY_EIGHT = 488,            /* "level-number 88"  */
    ENABLE = 489,                  /* ENABLE  */
    ELEMENT = 490,                 /* ELEMENT  */
    ELSE = 491,                    /* ELSE  */
    EMI = 492,                     /* EMI  */
    ENCRYPTION = 493,              /* ENCRYPTION  */
    ENCODING = 494,                /* ENCODING  */
    END = 495,                     /* END  */
    END_ACCEPT = 496,              /* "END-ACCEPT"  */
    END_ADD = 497,                 /* "END-ADD"  */
    END_CALL = 498,                /* "END-CALL"  */
    END_COMPUTE = 499,             /* "END-COMPUTE"  */
    END_COLOR = 500,               /* "END-COLOR"  */
    END_DELETE = 501,              /* "END-DELETE"  */
    END_DISPLAY = 502,             /* "END-DISPLAY"  */
    END_DIVIDE = 503,              /* "END-DIVIDE"  */
    END_EVALUATE = 504,            /* "END-EVALUATE"  */
    END_FUNCTION = 505,            /* "END FUNCTION"  */
    END_IF = 506,                  /* "END-IF"  */
    END_JSON = 507,                /* "END-JSON"  */
    END_MODIFY = 508,              /* "END-MODIFY"  */
    END_MULTIPLY = 509,            /* "END-MULTIPLY"  */
    END_PERFORM = 510,             /* "END-PERFORM"  */
    END_PROGRAM = 511,             /* "END PROGRAM"  */
    END_READ = 512,                /* "END-READ"  */
    END_RECEIVE = 513,             /* "END-RECEIVE"  */
    END_RETURN = 514,              /* "END-RETURN"  */
    END_REWRITE = 515,             /* "END-REWRITE"  */
    END_SEARCH = 516,              /* "END-SEARCH"  */
    END_START = 517,               /* "END-START"  */
    END_STRING = 518,              /* "END-STRING"  */
    END_SUBTRACT = 519,            /* "END-SUBTRACT"  */
    END_UNSTRING = 520,            /* "END-UNSTRING"  */
    END_WRITE = 521,               /* "END-WRITE"  */
    END_XML = 522,                 /* "END-XML"  */
    ENGRAVED = 523,                /* ENGRAVED  */
    ENSURE_VISIBLE = 524,          /* "ENSURE-VISIBLE"  */
    ENTRY = 525,                   /* ENTRY  */
    ENTRY_CONVENTION = 526,        /* "ENTRY-CONVENTION"  */
    ENTRY_FIELD = 527,             /* "ENTRY-FIELD"  */
    ENTRY_REASON = 528,            /* "ENTRY-REASON"  */
    ENVIRONMENT = 529,             /* ENVIRONMENT  */
    ENVIRONMENT_NAME = 530,        /* "ENVIRONMENT-NAME"  */
    ENVIRONMENT_VALUE = 531,       /* "ENVIRONMENT-VALUE"  */
    EOL = 532,                     /* EOL  */
    EOP = 533,                     /* EOP  */
    EOS = 534,                     /* EOS  */
    EQUAL = 535,                   /* EQUAL  */
    ERASE = 536,                   /* ERASE  */
    ERROR = 537,                   /* ERROR  */
    ESCAPE = 538,                  /* ESCAPE  */
    ESCAPE_BUTTON = 539,           /* "ESCAPE-BUTTON"  */
    ESI = 540,                     /* ESI  */
    EVALUATE = 541,                /* EVALUATE  */
    EVENT = 542,                   /* EVENT  */
    EVENT_LIST = 543,              /* "EVENT-LIST"  */
    EVENT_STATUS = 544,            /* "EVENT STATUS"  */
    EVERY = 545,                   /* EVERY  */
    EXCEPTION = 546,               /* EXCEPTION  */
    EXCEPTION_CONDITION = 547,     /* "EXCEPTION CONDITION"  */
    EXCEPTION_VALUE = 548,         /* "EXCEPTION-VALUE"  */
    EXPAND = 549,                  /* EXPAND  */
    EXCLUSIVE = 550,               /* EXCLUSIVE  */
    EXHIBIT = 551,                 /* EXHIBIT  */
    EXIT = 552,                    /* EXIT  */
    EXPONENTIATION = 553,          /* "exponentiation operator"  */
    EXTEND = 554,                  /* EXTEND  */
    EXTENDED_SEARCH = 555,         /* "EXTENDED-SEARCH"  */
    EXTERNAL = 556,                /* EXTERNAL  */
    EXTERNAL_FORM = 557,           /* "EXTERNAL-FORM"  */
    F = 558,                       /* F  */
    FD = 559,                      /* FD  */
    FH__FCD = 560,                 /* "FH--FCD"  */
    FH__KEYDEF = 561,              /* "FH--KEYDEF"  */
    FILE_CONTROL = 562,            /* "FILE-CONTROL"  */
    FILE_ID = 563,                 /* "FILE-ID"  */
    FILE_LIMIT = 564,              /* "FILE-LIMIT"  */
    FILE_LIMITS = 565,             /* "FILE-LIMITS"  */
    FILE_NAME = 566,               /* "FILE-NAME"  */
    FILE_POS = 567,                /* "FILE-POS"  */
    FILL_COLOR = 568,              /* "FILL-COLOR"  */
    FILL_COLOR2 = 569,             /* "FILL-COLOR2"  */
    FILL_PERCENT = 570,            /* "FILL-PERCENT"  */
    FILLER = 571,                  /* FILLER  */
    FINAL = 572,                   /* FINAL  */
    FINISH_REASON = 573,           /* "FINISH-REASON"  */
    FIRST = 574,                   /* FIRST  */
    FIXED = 575,                   /* FIXED  */
    FIXED_FONT = 576,              /* "FIXED-FONT"  */
    FIXED_WIDTH = 577,             /* "FIXED-WIDTH"  */
    FLAT = 578,                    /* FLAT  */
    FLAT_BUTTONS = 579,            /* "FLAT-BUTTONS"  */
    FLOAT_BINARY_128 = 580,        /* "FLOAT-BINARY-128"  */
    FLOAT_BINARY_32 = 581,         /* "FLOAT-BINARY-32"  */
    FLOAT_BINARY_64 = 582,         /* "FLOAT-BINARY-64"  */
    FLOAT_DECIMAL_16 = 583,        /* "FLOAT-DECIMAL-16"  */
    FLOAT_DECIMAL_34 = 584,        /* "FLOAT-DECIMAL-34"  */
    FLOAT_DECIMAL_7 = 585,         /* "FLOAT-DECIMAL-7"  */
    FLOAT_EXTENDED = 586,          /* "FLOAT-EXTENDED"  */
    FLOAT_LONG = 587,              /* "FLOAT-LONG"  */
    FLOAT_SHORT = 588,             /* "FLOAT-SHORT"  */
    FLOATING = 589,                /* FLOATING  */
    FONT = 590,                    /* FONT  */
    FOOTING = 591,                 /* FOOTING  */
    FOR = 592,                     /* FOR  */
    FOREGROUND_COLOR = 593,        /* "FOREGROUND-COLOR"  */
    FOREVER = 594,                 /* FOREVER  */
    FORMATTED_DATE_FUNC = 595,     /* "FUNCTION FORMATTED-DATE"  */
    FORMATTED_DATETIME_FUNC = 596, /* "FUNCTION FORMATTED-DATETIME"  */
    FORMATTED_TIME_FUNC = 597,     /* "FUNCTION FORMATTED-TIME"  */
    FRAME = 598,                   /* FRAME  */
    FRAMED = 599,                  /* FRAMED  */
    FREE = 600,                    /* FREE  */
    FROM = 601,                    /* FROM  */
    FROM_CRT = 602,                /* "FROM CRT"  */
    FULL = 603,                    /* FULL  */
    FULL_HEIGHT = 604,             /* "FULL-HEIGHT"  */
    FUNCTION = 605,                /* FUNCTION  */
    FUNCTION_ID = 606,             /* "FUNCTION-ID"  */
    FUNCTION_NAME = 607,           /* "intrinsic function name"  */
    GENERATE = 608,                /* GENERATE  */
    GIVING = 609,                  /* GIVING  */
    GLOBAL = 610,                  /* GLOBAL  */
    GO = 611,                      /* GO  */
    GO_BACK = 612,                 /* "GO-BACK"  */
    GO_FORWARD = 613,              /* "GO-FORWARD"  */
    GO_HOME = 614,                 /* "GO-HOME"  */
    GO_SEARCH = 615,               /* "GO-SEARCH"  */
    GOBACK = 616,                  /* GOBACK  */
    GRAPHICAL = 617,               /* GRAPHICAL  */
    GREATER = 618,                 /* GREATER  */
    GREATER_OR_EQUAL = 619,        /* "GREATER OR EQUAL"  */
    GRID = 620,                    /* GRID  */
    GROUP = 621,                   /* GROUP  */
    GROUP_VALUE = 622,             /* "GROUP-VALUE"  */
    HANDLE = 623,                  /* HANDLE  */
    HAS_CHILDREN = 624,            /* "HAS-CHILDREN"  */
    HEADING = 625,                 /* HEADING  */
    HEADING_COLOR = 626,           /* "HEADING-COLOR"  */
    HEADING_DIVIDER_COLOR = 627,   /* "HEADING-DIVIDER-COLOR"  */
    HEADING_FONT = 628,            /* "HEADING-FONT"  */
    HEAVY = 629,                   /* HEAVY  */
    HEIGHT_IN_CELLS = 630,         /* "HEIGHT-IN-CELLS"  */
    HIDDEN_DATA = 631,             /* "HIDDEN-DATA"  */
    HIGHLIGHT = 632,               /* HIGHLIGHT  */
    HIGH_COLOR = 633,              /* "HIGH-COLOR"  */
    HIGH_VALUE = 634,              /* "HIGH-VALUE"  */
    HOT_TRACK = 635,               /* "HOT-TRACK"  */
    HSCROLL = 636,                 /* HSCROLL  */
    HSCROLL_POS = 637,             /* "HSCROLL-POS"  */
    ICON = 638,                    /* ICON  */
    ID = 639,                      /* ID  */
    IDENTIFIED = 640,              /* IDENTIFIED  */
    IDENTIFICATION = 641,          /* IDENTIFICATION  */
    IF = 642,                      /* IF  */
    IGNORE = 643,                  /* IGNORE  */
    IGNORING = 644,                /* IGNORING  */
    IN = 645,                      /* IN  */
    INDEPENDENT = 646,             /* INDEPENDENT  */
    INDEX = 647,                   /* INDEX  */
    INDEXED = 648,                 /* INDEXED  */
    INDICATE = 649,                /* INDICATE  */
    INITIALIZE = 650,              /* INITIALIZE  */
    INITIALIZED = 651,             /* INITIALIZED  */
    INITIATE = 652,                /* INITIATE  */
    INPUT = 653,                   /* INPUT  */
    INPUT_OUTPUT = 654,            /* "INPUT-OUTPUT"  */
    INQUIRE = 655,                 /* INQUIRE  */
    INSERTION_INDEX = 656,         /* "INSERTION-INDEX"  */
    INSERT_ROWS = 657,             /* "INSERT-ROWS"  */
    INSPECT = 658,                 /* INSPECT  */
    INTERMEDIATE = 659,            /* INTERMEDIATE  */
    INTO = 660,                    /* INTO  */
    INTRINSIC = 661,               /* INTRINSIC  */
    INVALID = 662,                 /* INVALID  */
    INVALID_KEY = 663,             /* "INVALID KEY"  */
    IS = 664,                      /* IS  */
    ITEM = 665,                    /* ITEM  */
    ITEM_TEXT = 666,               /* "ITEM-TEXT"  */
    ITEM_TO_ADD = 667,             /* "ITEM-TO_ADD"  */
    ITEM_TO_DELETE = 668,          /* "ITEM-TO_DELETE"  */
    ITEM_TO_EMPTY = 669,           /* "ITEM-TO_EMPTY"  */
    ITEM_VALUE = 670,              /* "ITEM-VALUE"  */
    I_O = 671,                     /* "I-O"  */
    I_O_CONTROL = 672,             /* "I-O-CONTROL"  */
    JSON = 673,                    /* JSON  */
    JUSTIFIED = 674,               /* JUSTIFIED  */
    KEPT = 675,                    /* KEPT  */
    KEY = 676,                     /* KEY  */
    KEYBOARD = 677,                /* KEYBOARD  */
    LABEL = 678,                   /* LABEL  */
    LABEL_OFFSET = 679,            /* "LABEL-OFFSET"  */
    LARGE_FONT = 680,              /* "LARGE-FONT"  */
    LARGE_OFFSET = 681,            /* "LARGE-OFFSET"  */
    LAST = 682,                    /* LAST  */
    LAST_ROW = 683,                /* "LAST-ROW"  */
    LAYOUT_DATA = 684,             /* "LAYOUT-DATA"  */
    LAYOUT_MANAGER = 685,          /* "LAYOUT-MANAGER"  */
    LEADING = 686,                 /* LEADING  */
    LEADING_SHIFT = 687,           /* "LEADING-SHIFT"  */
    LEAVE = 688,                   /* LEAVE  */
    LEFT = 689,                    /* LEFT  */
    LEFTLINE = 690,                /* LEFTLINE  */
    LEFT_TEXT = 691,               /* "LEFT-TEXT"  */
    LENGTH = 692,                  /* LENGTH  */
    LENGTH_OF = 693,               /* "LENGTH OF"  */
    LENGTH_FUNC = 694,             /* "FUNCTION LENGTH/BYTE-LENGTH"  */
    LESS = 695,                    /* LESS  */
    LESS_OR_EQUAL = 696,           /* "LESS OR EQUAL"  */
    LEVEL_NUMBER = 697,            /* "level-number"  */
    LIKE = 698,                    /* LIKE  */
    LIMIT = 699,                   /* LIMIT  */
    LIMITS = 700,                  /* LIMITS  */
    LINAGE = 701,                  /* LINAGE  */
    LINAGE_COUNTER = 702,          /* "LINAGE-COUNTER"  */
    LINE = 703,                    /* LINE  */
    LINE_COUNTER = 704,            /* "LINE-COUNTER"  */
    LINE_LIMIT = 705,              /* "LINE LIMIT"  */
    LINE_SEQUENTIAL = 706,         /* "LINE-SEQUENTIAL"  */
    LINES = 707,                   /* LINES  */
    LINES_AT_ROOT = 708,           /* "LINES-AT-ROOT"  */
    LINKAGE = 709,                 /* LINKAGE  */
    LIST_BOX = 710,                /* "LIST-BOX"  */
    LITERAL = 711,                 /* "Literal"  */
    LM_RESIZE = 712,               /* "LM-RESIZE"  */
    LOC = 713,                     /* LOC  */
    LOCALE = 714,                  /* LOCALE  */
    LOCALE_DATE_FUNC = 715,        /* "FUNCTION LOCALE-DATE"  */
    LOCALE_TIME_FUNC = 716,        /* "FUNCTION LOCALE-TIME"  */
    LOCALE_TIME_FROM_FUNC = 717,   /* "FUNCTION LOCALE-TIME-FROM-SECONDS"  */
    LOCAL_STORAGE = 718,           /* "LOCAL-STORAGE"  */
    LOCK = 719,                    /* LOCK  */
    LOCK_HOLDING = 720,            /* "LOCK-HOLDING"  */
    LONG_DATE = 721,               /* "LONG-DATE"  */
    LOWER = 722,                   /* LOWER  */
    LOWERED = 723,                 /* LOWERED  */
    LOWER_CASE_FUNC = 724,         /* "FUNCTION LOWER-CASE"  */
    LOWLIGHT = 725,                /* LOWLIGHT  */
    LOW_COLOR = 726,               /* "LOW-COLOR"  */
    LOW_VALUE = 727,               /* "LOW-VALUE"  */
    MAGNETIC_TAPE = 728,           /* "MAGNETIC-TAPE"  */
    MANUAL = 729,                  /* MANUAL  */
    MASS_UPDATE = 730,             /* "MASS-UPDATE"  */
    MASTER_INDEX = 731,            /* "MASTER-INDEX"  */
    MAX_LINES = 732,               /* "MAX-LINES"  */
    MAX_PROGRESS = 733,            /* "MAX-PROGRESS"  */
    MAX_TEXT = 734,                /* "MAX-TEXT"  */
    MAX_VAL = 735,                 /* "MAX-VAL"  */
    MEMORY = 736,                  /* MEMORY  */
    MEDIUM_FONT = 737,             /* "MEDIUM-FONT"  */
    MENU = 738,                    /* MENU  */
    MERGE = 739,                   /* MERGE  */
    MESSAGE = 740,                 /* MESSAGE  */
    MINUS = 741,                   /* MINUS  */
    MIN_VAL = 742,                 /* "MIN-VAL"  */
    MNEMONIC_NAME = 743,           /* "Mnemonic name"  */
    MODE = 744,                    /* MODE  */
    MODIFY = 745,                  /* MODIFY  */
    MODULES = 746,                 /* MODULES  */
    MOVE = 747,                    /* MOVE  */
    MULTILINE = 748,               /* MULTILINE  */
    MULTIPLE = 749,                /* MULTIPLE  */
    MULTIPLY = 750,                /* MULTIPLY  */
    NAME = 751,                    /* NAME  */
    NAMED = 752,                   /* NAMED  */
    NAMESPACE = 753,               /* NAMESPACE  */
    NAMESPACE_PREFIX = 754,        /* "NAMESPACE-PREFIX"  */
    NATIONAL = 755,                /* NATIONAL  */
    NATIONAL_EDITED = 756,         /* "NATIONAL-EDITED"  */
    NATIONAL_OF_FUNC = 757,        /* "FUNCTION NATIONAL-OF"  */
    NATIVE = 758,                  /* NATIVE  */
    NAVIGATE_URL = 759,            /* "NAVIGATE-URL"  */
    NEAREST_AWAY_FROM_ZERO = 760,  /* "NEAREST-AWAY-FROM-ZERO"  */
    NEAREST_EVEN = 761,            /* "NEAREST-EVEN"  */
    NEAREST_TOWARD_ZERO = 762,     /* "NEAREST-TOWARD-ZERO"  */
    NEGATIVE = 763,                /* NEGATIVE  */
    NESTED = 764,                  /* NESTED  */
    NEW = 765,                     /* NEW  */
    NEXT = 766,                    /* NEXT  */
    NEXT_ITEM = 767,               /* "NEXT-ITEM"  */
    NEXT_GROUP = 768,              /* "NEXT GROUP"  */
    NEXT_PAGE = 769,               /* "NEXT PAGE"  */
    NO = 770,                      /* NO  */
    NO_ADVANCING = 771,            /* "NO ADVANCING"  */
    NO_AUTOSEL = 772,              /* "NO-AUTOSEL"  */
    NO_AUTO_DEFAULT = 773,         /* "NO-AUTO-DEFAULT"  */
    NO_BOX = 774,                  /* "NO-BOX"  */
    NO_DATA = 775,                 /* "NO DATA"  */
    NO_DIVIDERS = 776,             /* "NO-DIVIDERS"  */
    NO_ECHO = 777,                 /* "NO-ECHO"  */
    NO_F4 = 778,                   /* "NO-F4"  */
    NO_FOCUS = 779,                /* "NO-FOCUS"  */
    NO_GROUP_TAB = 780,            /* "NO-GROUP-TAB"  */
    NO_KEY_LETTER = 781,           /* "NO-KEY-LETTER"  */
    NOMINAL = 782,                 /* NOMINAL  */
    NO_SEARCH = 783,               /* "NO-SEARCH"  */
    NO_UPDOWN = 784,               /* "NO-UPDOWN"  */
    NONNUMERIC = 785,              /* NONNUMERIC  */
    NORMAL = 786,                  /* NORMAL  */
    NOT = 787,                     /* NOT  */
    NOTAB = 788,                   /* NOTAB  */
    NOTHING = 789,                 /* NOTHING  */
    NOTIFY = 790,                  /* NOTIFY  */
    NOTIFY_CHANGE = 791,           /* "NOTIFY-CHANGE"  */
    NOTIFY_DBLCLICK = 792,         /* "NOTIFY-DBLCLICK"  */
    NOTIFY_SELCHANGE = 793,        /* "NOTIFY-SELCHANGE"  */
    NOT_END = 794,                 /* "NOT END"  */
    NOT_EOP = 795,                 /* "NOT EOP"  */
    NOT_ESCAPE = 796,              /* "NOT ESCAPE"  */
    NOT_EQUAL = 797,               /* "NOT EQUAL"  */
    NOT_EXCEPTION = 798,           /* "NOT EXCEPTION"  */
    NOT_INVALID_KEY = 799,         /* "NOT INVALID KEY"  */
    NOT_OVERFLOW = 800,            /* "NOT OVERFLOW"  */
    NOT_SIZE_ERROR = 801,          /* "NOT SIZE ERROR"  */
    NUM_COL_HEADINGS = 802,        /* "NUM-COL-HEADINGS"  */
    NUM_ROWS = 803,                /* "NUM-ROWS"  */
    NUMBER = 804,                  /* NUMBER  */
    NUMBERS = 805,                 /* NUMBERS  */
    NUMERIC = 806,                 /* NUMERIC  */
    NUMERIC_EDITED = 807,          /* "NUMERIC-EDITED"  */
    NUMVALC_FUNC = 808,            /* "FUNCTION NUMVAL-C"  */
    OBJECT = 809,                  /* OBJECT  */
    OBJECT_COMPUTER = 810,         /* "OBJECT-COMPUTER"  */
    OCCURS = 811,                  /* OCCURS  */
    OF = 812,                      /* OF  */
    OFF = 813,                     /* OFF  */
    OK_BUTTON = 814,               /* "OK-BUTTON"  */
    OMITTED = 815,                 /* OMITTED  */
    ON = 816,                      /* ON  */
    ONLY = 817,                    /* ONLY  */
    OPEN = 818,                    /* OPEN  */
    OPTIONAL = 819,                /* OPTIONAL  */
    OPTIONS = 820,                 /* OPTIONS  */
    OR = 821,                      /* OR  */
    ORDER = 822,                   /* ORDER  */
    ORGANIZATION = 823,            /* ORGANIZATION  */
    OTHER = 824,                   /* OTHER  */
    OTHERS = 825,                  /* OTHERS  */
    OUTPUT = 826,                  /* OUTPUT  */
    OVERLAP_LEFT = 827,            /* "OVERLAP-LEFT"  */
    OVERLAP_TOP = 828,             /* "OVERLAP-TOP"  */
    OVERLINE = 829,                /* OVERLINE  */
    PACKED_DECIMAL = 830,          /* "PACKED-DECIMAL"  */
    PADDING = 831,                 /* PADDING  */
    PASCAL = 832,                  /* PASCAL  */
    PAGE = 833,                    /* PAGE  */
    PAGE_COUNTER = 834,            /* "PAGE-COUNTER"  */
    PAGE_SETUP = 835,              /* "PAGE-SETUP"  */
    PAGED = 836,                   /* PAGED  */
    PARAGRAPH = 837,               /* PARAGRAPH  */
    PARENT = 838,                  /* PARENT  */
    PARSE = 839,                   /* PARSE  */
    PASSWORD = 840,                /* PASSWORD  */
    PERFORM = 841,                 /* PERFORM  */
    PERMANENT = 842,               /* PERMANENT  */
    PH = 843,                      /* PH  */
    PF = 844,                      /* PF  */
    PHYSICAL = 845,                /* PHYSICAL  */
    PICTURE = 846,                 /* PICTURE  */
    PICTURE_SYMBOL = 847,          /* "PICTURE SYMBOL"  */
    PIXEL = 848,                   /* PIXEL  */
    PLACEMENT = 849,               /* PLACEMENT  */
    PLUS = 850,                    /* PLUS  */
    POINTER = 851,                 /* POINTER  */
    POP_UP = 852,                  /* "POP-UP"  */
    POS = 853,                     /* POS  */
    POSITION = 854,                /* POSITION  */
    POSITION_SHIFT = 855,          /* "POSITION-SHIFT"  */
    POSITIVE = 856,                /* POSITIVE  */
    PRESENT = 857,                 /* PRESENT  */
    PREVIOUS = 858,                /* PREVIOUS  */
    PRINT = 859,                   /* PRINT  */
    PRINT_CONTROL = 860,           /* "PRINT-CONTROL"  */
    PRINT_NO_PROMPT = 861,         /* "PRINT-NO-PROMPT"  */
    PRINT_PREVIEW = 862,           /* "PRINT-PREVIEW"  */
    PRINTER = 863,                 /* PRINTER  */
    PRINTER_1 = 864,               /* "PRINTER-1"  */
    PRINTING = 865,                /* PRINTING  */
    PRIORITY = 866,                /* PRIORITY  */
    PROCEDURE = 867,               /* PROCEDURE  */
    PROCEDURES = 868,              /* PROCEDURES  */
    PROCEED = 869,                 /* PROCEED  */
    PROCESSING = 870,              /* PROCESSING  */
    PROGRAM = 871,                 /* PROGRAM  */
    PROGRAM_ID = 872,              /* "PROGRAM-ID"  */
    PROGRAM_NAME = 873,            /* "program name"  */
    PROGRAM_POINTER = 874,         /* "PROGRAM-POINTER"  */
    PROGRESS = 875,                /* PROGRESS  */
    PROHIBITED = 876,              /* PROHIBITED  */
    PROMPT = 877,                  /* PROMPT  */
    PROPERTIES = 878,              /* PROPERTIES  */
    PROPERTY = 879,                /* PROPERTY  */
    PROTECTED = 880,               /* PROTECTED  */
    PURGE = 881,                   /* PURGE  */
    PUSH_BUTTON = 882,             /* "PUSH-BUTTON"  */
    QUERY_INDEX = 883,             /* "QUERY-INDEX"  */
    QUEUE = 884,                   /* QUEUE  */
    QUOTE = 885,                   /* QUOTE  */
    RADIO_BUTTON = 886,            /* "RADIO-BUTTON"  */
    RAISE = 887,                   /* RAISE  */
    RAISED = 888,                  /* RAISED  */
    RANDOM = 889,                  /* RANDOM  */
    RD = 890,                      /* RD  */
    READ = 891,                    /* READ  */
    READERS = 892,                 /* READERS  */
    READ_ONLY = 893,               /* "READ-ONLY"  */
    READY_TRACE = 894,             /* "READY TRACE"  */
    RECEIVE = 895,                 /* RECEIVE  */
    RECORD = 896,                  /* RECORD  */
    RECORD_DATA = 897,             /* "RECORD-DATA"  */
    RECORD_OVERFLOW = 898,         /* "RECORD-OVERFLOW"  */
    RECORD_TO_ADD = 899,           /* "RECORD-TO-ADD"  */
    RECORD_TO_DELETE = 900,        /* "RECORD-TO-DELETE"  */
    RECORDING = 901,               /* RECORDING  */
    RECORDS = 902,                 /* RECORDS  */
    RECURSIVE = 903,               /* RECURSIVE  */
    REDEFINES = 904,               /* REDEFINES  */
    REEL = 905,                    /* REEL  */
    REFERENCE = 906,               /* REFERENCE  */
    REFERENCES = 907,              /* REFERENCES  */
    REFRESH = 908,                 /* REFRESH  */
    REGION_COLOR = 909,            /* "REGION-COLOR"  */
    RELATIVE = 910,                /* RELATIVE  */
    RELEASE = 911,                 /* RELEASE  */
    REMAINDER = 912,               /* REMAINDER  */
    REMOVAL = 913,                 /* REMOVAL  */
    RENAMES = 914,                 /* RENAMES  */
    REORG_CRITERIA = 915,          /* "REORG-CRITERIA"  */
    REPLACE = 916,                 /* REPLACE  */
    REPLACING = 917,               /* REPLACING  */
    REPORT = 918,                  /* REPORT  */
    REPORTING = 919,               /* REPORTING  */
    REPORTS = 920,                 /* REPORTS  */
    REPOSITORY = 921,              /* REPOSITORY  */
    REQUIRED = 922,                /* REQUIRED  */
    REREAD = 923,                  /* REREAD  */
    RERUN = 924,                   /* RERUN  */
    RESERVE = 925,                 /* RESERVE  */
    RESET = 926,                   /* RESET  */
    RESET_TRACE = 927,             /* "RESET TRACE"  */
    RESET_GRID = 928,              /* "RESET-GRID"  */
    RESET_LIST = 929,              /* "RESET-LIST"  */
    RESET_TABS = 930,              /* "RESET-TABS"  */
    RETRY = 931,                   /* RETRY  */
    RETURN = 932,                  /* RETURN  */
    RETURNING = 933,               /* RETURNING  */
    REVERSE = 934,                 /* REVERSE  */
    REVERSE_FUNC = 935,            /* "FUNCTION REVERSE"  */
    REVERSE_VIDEO = 936,           /* "REVERSE-VIDEO"  */
    REVERSED = 937,                /* REVERSED  */
    REWIND = 938,                  /* REWIND  */
    REWRITE = 939,                 /* REWRITE  */
    RF = 940,                      /* RF  */
    RH = 941,                      /* RH  */
    RIGHT = 942,                   /* RIGHT  */
    RIGHT_ALIGN = 943,             /* "RIGHT-ALIGN"  */
    RIMMED = 944,                  /* RIMMED  */
    ROLLBACK = 945,                /* ROLLBACK  */
    ROUNDED = 946,                 /* ROUNDED  */
    ROUNDING = 947,                /* ROUNDING  */
    ROW_COLOR = 948,               /* "ROW-COLOR"  */
    ROW_COLOR_PATTERN = 949,       /* "ROW-COLOR-PATTERN"  */
    ROW_DIVIDERS = 950,            /* "ROW-DIVIDERS"  */
    ROW_FONT = 951,                /* "ROW-FONT"  */
    ROW_HEADINGS = 952,            /* "ROW-HEADINGS"  */
    ROW_PROTECTION = 953,          /* "ROW-PROTECTION"  */
    RUN = 954,                     /* RUN  */
    S = 955,                       /* S  */
    SAME = 956,                    /* SAME  */
    SAVE_AS = 957,                 /* "SAVE-AS"  */
    SAVE_AS_NO_PROMPT = 958,       /* "SAVE-AS-NO-PROMPT"  */
    SCREEN = 959,                  /* SCREEN  */
    SCREEN_CONTROL = 960,          /* "SCREEN CONTROL"  */
    SCROLL = 961,                  /* SCROLL  */
    SCROLL_BAR = 962,              /* "SCROLL-BAR"  */
    SD = 963,                      /* SD  */
    SEARCH = 964,                  /* SEARCH  */
    SEARCH_OPTIONS = 965,          /* "SEARCH-OPTIONS"  */
    SEARCH_TEXT = 966,             /* "SEARCH-TEXT"  */
    SECONDS = 967,                 /* SECONDS  */
    SECTION = 968,                 /* SECTION  */
    SECURE = 969,                  /* SECURE  */
    SEGMENT = 970,                 /* SEGMENT  */
    SEGMENT_LIMIT = 971,           /* "SEGMENT-LIMIT"  */
    SELECT = 972,                  /* SELECT  */
    SELECTION_INDEX = 973,         /* "SELECTION-INDEX"  */
    SELECTION_TEXT = 974,          /* "SELECTION-TEXT"  */
    SELECT_ALL = 975,              /* "SELECTION-ALL"  */
    SELF_ACT = 976,                /* "SELF-ACT"  */
    SEMI_COLON = 977,              /* "semi-colon"  */
    SEND = 978,                    /* SEND  */
    SENTENCE = 979,                /* SENTENCE  */
    SEPARATE = 980,                /* SEPARATE  */
    SEPARATION = 981,              /* SEPARATION  */
    SEQUENCE = 982,                /* SEQUENCE  */
    SEQUENTIAL = 983,              /* SEQUENTIAL  */
    SET = 984,                     /* SET  */
    SEVENTY_EIGHT = 985,           /* "level-number 78"  */
    SHADING = 986,                 /* SHADING  */
    SHADOW = 987,                  /* SHADOW  */
    SHARING = 988,                 /* SHARING  */
    SHORT_DATE = 989,              /* "SHORT-DATE"  */
    SHOW_LINES = 990,              /* "SHOW-LINES"  */
    SHOW_NONE = 991,               /* "SHOW-NONE"  */
    SHOW_SEL_ALWAYS = 992,         /* "SHOW-SEL-ALWAYS"  */
    SIGN = 993,                    /* SIGN  */
    SIGNED = 994,                  /* SIGNED  */
    SIGNED_INT = 995,              /* "SIGNED-INT"  */
    SIGNED_LONG = 996,             /* "SIGNED-LONG"  */
    SIGNED_SHORT = 997,            /* "SIGNED-SHORT"  */
    SIXTY_SIX = 998,               /* "level-number 66"  */
    SIZE = 999,                    /* SIZE  */
    SIZE_ERROR = 1000,             /* "SIZE ERROR"  */
    SMALL_FONT = 1001,             /* "SMALL-FONT"  */
    SORT = 1002,                   /* SORT  */
    SORT_MERGE = 1003,             /* "SORT-MERGE"  */
    SORT_ORDER = 1004,             /* "SORT-ORDER"  */
    SOURCE = 1005,                 /* SOURCE  */
    SOURCE_COMPUTER = 1006,        /* "SOURCE-COMPUTER"  */
    SPACE = 1007,                  /* SPACE  */
    SPECIAL_NAMES = 1008,          /* "SPECIAL-NAMES"  */
    SPINNER = 1009,                /* SPINNER  */
    SQUARE = 1010,                 /* SQUARE  */
    STANDARD = 1011,               /* STANDARD  */
    STANDARD_1 = 1012,             /* "STANDARD-1"  */
    STANDARD_2 = 1013,             /* "STANDARD-2"  */
    STANDARD_BINARY = 1014,        /* "STANDARD-BINARY"  */
    STANDARD_DECIMAL = 1015,       /* "STANDARD-DECIMAL"  */
    START = 1016,                  /* START  */
    START_X = 1017,                /* "START-X"  */
    START_Y = 1018,                /* "START-Y"  */
    STATIC = 1019,                 /* STATIC  */
    STATIC_LIST = 1020,            /* "STATIC-LIST"  */
    STATUS = 1021,                 /* STATUS  */
    STATUS_BAR = 1022,             /* "STATUS-BAR"  */
    STATUS_TEXT = 1023,            /* "STATUS-TEXT"  */
    STDCALL = 1024,                /* STDCALL  */
    STEP = 1025,                   /* STEP  */
    STOP = 1026,                   /* STOP  */
    STRING = 1027,                 /* STRING  */
    STRONG = 1028,                 /* STRONG  */
    STYLE = 1029,                  /* STYLE  */
    SUB_QUEUE_1 = 1030,            /* "SUB-QUEUE-1"  */
    SUB_QUEUE_2 = 1031,            /* "SUB-QUEUE-2"  */
    SUB_QUEUE_3 = 1032,            /* "SUB-QUEUE-3"  */
    SUBSTITUTE_FUNC = 1033,        /* "FUNCTION SUBSTITUTE"  */
    SUBSTITUTE_CASE_FUNC = 1034,   /* "FUNCTION SUBSTITUTE-CASE"  */
    SUBTRACT = 1035,               /* SUBTRACT  */
    SUBWINDOW = 1036,              /* SUBWINDOW  */
    SUM = 1037,                    /* SUM  */
    SUPPRESS = 1038,               /* SUPPRESS  */
    SUPPRESS_XML = 1039,           /* "SUPPRESS"  */
    SYMBOLIC = 1040,               /* SYMBOLIC  */
    SYNCHRONIZED = 1041,           /* SYNCHRONIZED  */
    SYSTEM_DEFAULT = 1042,         /* "SYSTEM-DEFAULT"  */
    SYSTEM_INFO = 1043,            /* "SYSTEM-INFO"  */
    SYSTEM_OFFSET = 1044,          /* "SYSTEM-OFFSET"  */
    TAB = 1045,                    /* TAB  */
    TAB_TO_ADD = 1046,             /* "TAB-TO-ADD"  */
    TAB_TO_DELETE = 1047,          /* "TAB-TO-DELETE"  */
    TABLE = 1048,                  /* TABLE  */
    TALLYING = 1049,               /* TALLYING  */
    TEMPORARY = 1050,              /* TEMPORARY  */
    TAPE = 1051,                   /* TAPE  */
    TERMINAL = 1052,               /* TERMINAL  */
    TERMINATE = 1053,              /* TERMINATE  */
    TERMINAL_INFO = 1054,          /* "TERMINAL-INFO"  */
    TERMINATION_VALUE = 1055,      /* "TERMINATION-VALUE"  */
    TEST = 1056,                   /* TEST  */
    TEXT = 1057,                   /* TEXT  */
    THAN = 1058,                   /* THAN  */
    THEN = 1059,                   /* THEN  */
    THREAD = 1060,                 /* THREAD  */
    THREADS = 1061,                /* THREADS  */
    THRU = 1062,                   /* THRU  */
    THUMB_POSITION = 1063,         /* "THUMB-POSITION"  */
    TILED_HEADINGS = 1064,         /* "TILED-HEADINGS"  */
    TIME = 1065,                   /* TIME  */
    TIME_OUT = 1066,               /* "TIME-OUT"  */
    TIMES = 1067,                  /* TIMES  */
    TITLE = 1068,                  /* TITLE  */
    TITLE_POSITION = 1069,         /* "TITLE-POSITION"  */
    TO = 1070,                     /* TO  */
    TOK_AMPER = 1071,              /* "&"  */
    TOK_CLOSE_PAREN = 1072,        /* ")"  */
    TOK_COLON = 1073,              /* ":"  */
    TOK_DIV = 1074,                /* "/"  */
    TOK_DOT = 1075,                /* "."  */
    TOK_EQUAL = 1076,              /* "="  */
    TOK_EXTERN = 1077,             /* "EXTERN"  */
    TOK_FALSE = 1078,              /* "FALSE"  */
    TOK_FILE = 1079,               /* "FILE"  */
    TOK_GREATER = 1080,            /* ">"  */
    TOK_INITIAL = 1081,            /* "INITIAL"  */
    TOK_LESS = 1082,               /* "<"  */
    TOK_MINUS = 1083,              /* "-"  */
    TOK_MUL = 1084,                /* "*"  */
    TOK_NULL = 1085,               /* "NULL"  */
    TOK_OVERFLOW = 1086,           /* "OVERFLOW"  */
    TOK_OPEN_PAREN = 1087,         /* "("  */
    TOK_PLUS = 1088,               /* "+"  */
    TOK_TRUE = 1089,               /* "TRUE"  */
    TOP = 1090,                    /* TOP  */
    TOWARD_GREATER = 1091,         /* "TOWARD-GREATER"  */
    TOWARD_LESSER = 1092,          /* "TOWARD-LESSER"  */
    TRACK = 1093,                  /* TRACK  */
    TRACKS = 1094,                 /* TRACKS  */
    TRACK_AREA = 1095,             /* "TRACK-AREA"  */
    TRACK_LIMIT = 1096,            /* "TRACK-LIMIT"  */
    TRADITIONAL_FONT = 1097,       /* "TRADITIONAL-FONT"  */
    TRAILING = 1098,               /* TRAILING  */
    TRAILING_SHIFT = 1099,         /* "TRAILING-SHIFT"  */
    TRANSFORM = 1100,              /* TRANSFORM  */
    TRANSPARENT = 1101,            /* TRANSPARENT  */
    TREE_VIEW = 1102,              /* "TREE-VIEW"  */
    TRIM_FUNC = 1103,              /* "FUNCTION TRIM"  */
    TRUNCATION = 1104,             /* TRUNCATION  */
    TYPE = 1105,                   /* TYPE  */
    TYPEDEF = 1106,                /* TYPEDEF  */
    U = 1107,                      /* U  */
    UCS_4 = 1108,                  /* "UCS-4"  */
    UNBOUNDED = 1109,              /* UNBOUNDED  */
    UNDERLINE = 1110,              /* UNDERLINE  */
    UNFRAMED = 1111,               /* UNFRAMED  */
    UNIT = 1112,                   /* UNIT  */
    UNLOCK = 1113,                 /* UNLOCK  */
    UNSIGNED = 1114,               /* UNSIGNED  */
    UNSIGNED_INT = 1115,           /* "UNSIGNED-INT"  */
    UNSIGNED_LONG = 1116,          /* "UNSIGNED-LONG"  */
    UNSIGNED_SHORT = 1117,         /* "UNSIGNED-SHORT"  */
    UNSORTED = 1118,               /* UNSORTED  */
    UNSTRING = 1119,               /* UNSTRING  */
    UNTIL = 1120,                  /* UNTIL  */
    UP = 1121,                     /* UP  */
    UPDATE = 1122,                 /* UPDATE  */
    UPDATERS = 1123,               /* UPDATERS  */
    UPON = 1124,                   /* UPON  */
    UPON_ARGUMENT_NUMBER = 1125,   /* "UPON ARGUMENT-NUMBER"  */
    UPON_COMMAND_LINE = 1126,      /* "UPON COMMAND-LINE"  */
    UPON_ENVIRONMENT_NAME = 1127,  /* "UPON ENVIRONMENT-NAME"  */
    UPON_ENVIRONMENT_VALUE = 1128, /* "UPON ENVIRONMENT-VALUE"  */
    UPPER = 1129,                  /* UPPER  */
    UPPER_CASE_FUNC = 1130,        /* "FUNCTION UPPER-CASE"  */
    USAGE = 1131,                  /* USAGE  */
    USE = 1132,                    /* USE  */
    USE_ALT = 1133,                /* "USE-ALT"  */
    USE_RETURN = 1134,             /* "USE-RETURN"  */
    USE_TAB = 1135,                /* "USE-TAB"  */
    USER = 1136,                   /* USER  */
    USER_DEFAULT = 1137,           /* "USER-DEFAULT"  */
    USER_FUNCTION_NAME = 1138,     /* "user function name"  */
    USING = 1139,                  /* USING  */
    UTF_8 = 1140,                  /* "UTF-8"  */
    UTF_16 = 1141,                 /* "UTF-16"  */
    V = 1142,                      /* V  */
    VALIDATE = 1143,               /* VALIDATE  */
    VALIDATING = 1144,             /* VALIDATING  */
    VALUE = 1145,                  /* VALUE  */
    VALUE_FORMAT = 1146,           /* "VALUE-FORMAT"  */
    VARIABLE = 1147,               /* VARIABLE  */
    VARIANT = 1148,                /* VARIANT  */
    VARYING = 1149,                /* VARYING  */
    VERTICAL = 1150,               /* VERTICAL  */
    VERY_HEAVY = 1151,             /* "VERY-HEAVY"  */
    VIRTUAL_WIDTH = 1152,          /* "VIRTUAL-WIDTH"  */
    VOLATILE = 1153,               /* VOLATILE  */
    VPADDING = 1154,               /* VPADDING  */
    VSCROLL = 1155,                /* VSCROLL  */
    VSCROLL_BAR = 1156,            /* "VSCROLL-BAR"  */
    VSCROLL_POS = 1157,            /* "VSCROLL-POS"  */
    VTOP = 1158,                   /* VTOP  */
    WAIT = 1159,                   /* WAIT  */
    WEB_BROWSER = 1160,            /* "WEB-BROWSER"  */
    WHEN = 1161,                   /* WHEN  */
    WHEN_COMPILED_FUNC = 1162,     /* "FUNCTION WHEN-COMPILED"  */
    WHEN_XML = 1163,               /* "WHEN"  */
    WIDTH = 1164,                  /* WIDTH  */
    WIDTH_IN_CELLS = 1165,         /* "WIDTH-IN-CELLS"  */
    WINDOW = 1166,                 /* WINDOW  */
    WITH = 1167,                   /* WITH  */
    WORD = 1168,                   /* "Identifier"  */
    WORDS = 1169,                  /* WORDS  */
    WORKING_STORAGE = 1170,        /* "WORKING-STORAGE"  */
    WRAP = 1171,                   /* WRAP  */
    WRITE = 1172,                  /* WRITE  */
    WRITE_ONLY = 1173,             /* "WRITE-ONLY"  */
    WRITE_VERIFY = 1174,           /* "WRITE-VERIFY"  */
    WRITERS = 1175,                /* WRITERS  */
    X = 1176,                      /* X  */
    XML = 1177,                    /* XML  */
    XML_DECLARATION = 1178,        /* "XML-DECLARATION"  */
    Y = 1179,                      /* Y  */
    YYYYDDD = 1180,                /* YYYYDDD  */
    YYYYMMDD = 1181,               /* YYYYMMDD  */
    ZERO = 1182,                   /* ZERO  */
    SHIFT_PREFER = 1183            /* SHIFT_PREFER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define TOKEN_EOF 0
#define YYerror 256
#define YYUNDEF 257
#define THREEDIMENSIONAL 258
#define ABSENT 259
#define ACCEPT 260
#define ACCESS 261
#define ACTIVEX 262
#define ACTION 263
#define ACTUAL 264
#define ADD 265
#define ADDRESS 266
#define ADJUSTABLE_COLUMNS 267
#define ADVANCING 268
#define AFTER 269
#define ALIGNMENT 270
#define ALL 271
#define ALLOCATE 272
#define ALLOWING 273
#define ALPHABET 274
#define ALPHABETIC 275
#define ALPHABETIC_LOWER 276
#define ALPHABETIC_UPPER 277
#define ALPHANUMERIC 278
#define ALPHANUMERIC_EDITED 279
#define ALSO 280
#define ALTER 281
#define ALTERNATE 282
#define AND 283
#define ANY 284
#define APPLY 285
#define ARE 286
#define AREA 287
#define AREAS 288
#define ARGUMENT_NUMBER 289
#define ARGUMENT_VALUE 290
#define ARITHMETIC 291
#define AS 292
#define ASCENDING 293
#define ASCII 294
#define ASSIGN 295
#define AT 296
#define ATTRIBUTE 297
#define ATTRIBUTES 298
#define AUTO 299
#define AUTO_DECIMAL 300
#define AUTO_SPIN 301
#define AUTOMATIC 302
#define AWAY_FROM_ZERO 303
#define BACKGROUND_COLOR 304
#define BACKGROUND_HIGH 305
#define BACKGROUND_LOW 306
#define BACKGROUND_STANDARD 307
#define BAR 308
#define BASED 309
#define BEFORE 310
#define BELL 311
#define BINARY 312
#define BINARY_C_LONG 313
#define BINARY_CHAR 314
#define BINARY_DOUBLE 315
#define BINARY_LONG 316
#define BINARY_SEQUENTIAL 317
#define BINARY_SHORT 318
#define BIT 319
#define BITMAP 320
#define BITMAP_END 321
#define BITMAP_HANDLE 322
#define BITMAP_NUMBER 323
#define BITMAP_START 324
#define BITMAP_TIMER 325
#define BITMAP_TRAILING 326
#define BITMAP_TRANSPARENT_COLOR 327
#define BITMAP_WIDTH 328
#define BLANK 329
#define BLINK 330
#define BLOCK 331
#define BOTTOM 332
#define BOX 333
#define BOXED 334
#define BULK_ADDITION 335
#define BUSY 336
#define BUTTONS 337
#define BY 338
#define BYTE_LENGTH 339
#define C 340
#define CALENDAR_FONT 341
#define CALL 342
#define CANCEL 343
#define CANCEL_BUTTON 344
#define CAPACITY 345
#define CARD_PUNCH 346
#define CARD_READER 347
#define CASSETTE 348
#define CCOL 349
#define CD 350
#define CELL 351
#define CELL_COLOR 352
#define CELL_DATA 353
#define CELL_FONT 354
#define CELL_PROTECTION 355
#define CENTER 356
#define CENTERED 357
#define CENTERED_HEADINGS 358
#define CENTURY_DATE 359
#define CF 360
#define CH 361
#define CHAINING 362
#define CHANGED 363
#define CHARACTER 364
#define CHARACTERS 365
#define CHECK_BOX 366
#define CLASS 367
#define CLASSIFICATION 368
#define CLASS_NAME 369
#define CLEAR_SELECTION 370
#define CLINE 371
#define CLINES 372
#define CLOSE 373
#define COBOL 374
#define CODE 375
#define CODE_SET 376
#define COLLATING 377
#define COL 378
#define COLOR 379
#define COLORS 380
#define COLS 381
#define COLUMN 382
#define COLUMN_COLOR 383
#define COLUMN_DIVIDERS 384
#define COLUMN_FONT 385
#define COLUMN_HEADINGS 386
#define COLUMN_PROTECTION 387
#define COLUMNS 388
#define COMBO_BOX 389
#define COMMA 390
#define COMMAND_LINE 391
#define COMMA_DELIM 392
#define COMMIT 393
#define COMMON 394
#define COMMUNICATION 395
#define COMP 396
#define COMPUTE 397
#define COMP_0 398
#define COMP_1 399
#define COMP_2 400
#define COMP_3 401
#define COMP_4 402
#define COMP_5 403
#define COMP_6 404
#define COMP_N 405
#define COMP_X 406
#define CONCATENATE_FUNC 407
#define CONDITION 408
#define CONFIGURATION 409
#define CONSTANT 410
#define CONTAINS 411
#define CONTENT 412
#define CONTENT_LENGTH_FUNC 413
#define CONTENT_OF_FUNC 414
#define CONTINUE 415
#define CONTROL 416
#define CONTROLS 417
#define CONVERSION 418
#define CONVERTING 419
#define COPY 420
#define COPY_SELECTION 421
#define CORE_INDEX 422
#define CORRESPONDING 423
#define COUNT 424
#define CRT 425
#define CRT_UNDER 426
#define CSIZE 427
#define CURRENCY 428
#define CURRENT_DATE_FUNC 429
#define CURSOR 430
#define CURSOR_COL 431
#define CURSOR_COLOR 432
#define CURSOR_FRAME_WIDTH 433
#define CURSOR_ROW 434
#define CURSOR_X 435
#define CURSOR_Y 436
#define CUSTOM_PRINT_TEMPLATE 437
#define CYCLE 438
#define CYL_INDEX 439
#define CYL_OVERFLOW 440
#define DASHED 441
#define DATA 442
#define DATA_COLUMNS 443
#define DATA_TYPES 444
#define DATE 445
#define DATE_ENTRY 446
#define DAY 447
#define DAY_OF_WEEK 448
#define DE 449
#define DEBUGGING 450
#define DECIMAL_POINT 451
#define DECLARATIVES 452
#define DEFAULT 453
#define DEFAULT_BUTTON 454
#define DEFAULT_FONT 455
#define DELETE 456
#define DELIMITED 457
#define DELIMITER 458
#define DEPENDING 459
#define DESCENDING 460
#define DESTINATION 461
#define DESTROY 462
#define DETAIL 463
#define DISABLE 464
#define DISC 465
#define DISK 466
#define DISP 467
#define DISPLAY 468
#define DISPLAY_COLUMNS 469
#define DISPLAY_FORMAT 470
#define DISPLAY_OF_FUNC 471
#define DIVIDE 472
#define DIVIDERS 473
#define DIVIDER_COLOR 474
#define DIVISION 475
#define DOTDASH 476
#define DOTTED 477
#define DRAG_COLOR 478
#define DROP_DOWN 479
#define DROP_LIST 480
#define DOWN 481
#define DUPLICATES 482
#define DYNAMIC 483
#define EBCDIC 484
#define EC 485
#define ECHO 486
#define EGI 487
#define EIGHTY_EIGHT 488
#define ENABLE 489
#define ELEMENT 490
#define ELSE 491
#define EMI 492
#define ENCRYPTION 493
#define ENCODING 494
#define END 495
#define END_ACCEPT 496
#define END_ADD 497
#define END_CALL 498
#define END_COMPUTE 499
#define END_COLOR 500
#define END_DELETE 501
#define END_DISPLAY 502
#define END_DIVIDE 503
#define END_EVALUATE 504
#define END_FUNCTION 505
#define END_IF 506
#define END_JSON 507
#define END_MODIFY 508
#define END_MULTIPLY 509
#define END_PERFORM 510
#define END_PROGRAM 511
#define END_READ 512
#define END_RECEIVE 513
#define END_RETURN 514
#define END_REWRITE 515
#define END_SEARCH 516
#define END_START 517
#define END_STRING 518
#define END_SUBTRACT 519
#define END_UNSTRING 520
#define END_WRITE 521
#define END_XML 522
#define ENGRAVED 523
#define ENSURE_VISIBLE 524
#define ENTRY 525
#define ENTRY_CONVENTION 526
#define ENTRY_FIELD 527
#define ENTRY_REASON 528
#define ENVIRONMENT 529
#define ENVIRONMENT_NAME 530
#define ENVIRONMENT_VALUE 531
#define EOL 532
#define EOP 533
#define EOS 534
#define EQUAL 535
#define ERASE 536
#define ERROR 537
#define ESCAPE 538
#define ESCAPE_BUTTON 539
#define ESI 540
#define EVALUATE 541
#define EVENT 542
#define EVENT_LIST 543
#define EVENT_STATUS 544
#define EVERY 545
#define EXCEPTION 546
#define EXCEPTION_CONDITION 547
#define EXCEPTION_VALUE 548
#define EXPAND 549
#define EXCLUSIVE 550
#define EXHIBIT 551
#define EXIT 552
#define EXPONENTIATION 553
#define EXTEND 554
#define EXTENDED_SEARCH 555
#define EXTERNAL 556
#define EXTERNAL_FORM 557
#define F 558
#define FD 559
#define FH__FCD 560
#define FH__KEYDEF 561
#define FILE_CONTROL 562
#define FILE_ID 563
#define FILE_LIMIT 564
#define FILE_LIMITS 565
#define FILE_NAME 566
#define FILE_POS 567
#define FILL_COLOR 568
#define FILL_COLOR2 569
#define FILL_PERCENT 570
#define FILLER 571
#define FINAL 572
#define FINISH_REASON 573
#define FIRST 574
#define FIXED 575
#define FIXED_FONT 576
#define FIXED_WIDTH 577
#define FLAT 578
#define FLAT_BUTTONS 579
#define FLOAT_BINARY_128 580
#define FLOAT_BINARY_32 581
#define FLOAT_BINARY_64 582
#define FLOAT_DECIMAL_16 583
#define FLOAT_DECIMAL_34 584
#define FLOAT_DECIMAL_7 585
#define FLOAT_EXTENDED 586
#define FLOAT_LONG 587
#define FLOAT_SHORT 588
#define FLOATING 589
#define FONT 590
#define FOOTING 591
#define FOR 592
#define FOREGROUND_COLOR 593
#define FOREVER 594
#define FORMATTED_DATE_FUNC 595
#define FORMATTED_DATETIME_FUNC 596
#define FORMATTED_TIME_FUNC 597
#define FRAME 598
#define FRAMED 599
#define FREE 600
#define FROM 601
#define FROM_CRT 602
#define FULL 603
#define FULL_HEIGHT 604
#define FUNCTION 605
#define FUNCTION_ID 606
#define FUNCTION_NAME 607
#define GENERATE 608
#define GIVING 609
#define GLOBAL 610
#define GO 611
#define GO_BACK 612
#define GO_FORWARD 613
#define GO_HOME 614
#define GO_SEARCH 615
#define GOBACK 616
#define GRAPHICAL 617
#define GREATER 618
#define GREATER_OR_EQUAL 619
#define GRID 620
#define GROUP 621
#define GROUP_VALUE 622
#define HANDLE 623
#define HAS_CHILDREN 624
#define HEADING 625
#define HEADING_COLOR 626
#define HEADING_DIVIDER_COLOR 627
#define HEADING_FONT 628
#define HEAVY 629
#define HEIGHT_IN_CELLS 630
#define HIDDEN_DATA 631
#define HIGHLIGHT 632
#define HIGH_COLOR 633
#define HIGH_VALUE 634
#define HOT_TRACK 635
#define HSCROLL 636
#define HSCROLL_POS 637
#define ICON 638
#define ID 639
#define IDENTIFIED 640
#define IDENTIFICATION 641
#define IF 642
#define IGNORE 643
#define IGNORING 644
#define IN 645
#define INDEPENDENT 646
#define INDEX 647
#define INDEXED 648
#define INDICATE 649
#define INITIALIZE 650
#define INITIALIZED 651
#define INITIATE 652
#define INPUT 653
#define INPUT_OUTPUT 654
#define INQUIRE 655
#define INSERTION_INDEX 656
#define INSERT_ROWS 657
#define INSPECT 658
#define INTERMEDIATE 659
#define INTO 660
#define INTRINSIC 661
#define INVALID 662
#define INVALID_KEY 663
#define IS 664
#define ITEM 665
#define ITEM_TEXT 666
#define ITEM_TO_ADD 667
#define ITEM_TO_DELETE 668
#define ITEM_TO_EMPTY 669
#define ITEM_VALUE 670
#define I_O 671
#define I_O_CONTROL 672
#define JSON 673
#define JUSTIFIED 674
#define KEPT 675
#define KEY 676
#define KEYBOARD 677
#define LABEL 678
#define LABEL_OFFSET 679
#define LARGE_FONT 680
#define LARGE_OFFSET 681
#define LAST 682
#define LAST_ROW 683
#define LAYOUT_DATA 684
#define LAYOUT_MANAGER 685
#define LEADING 686
#define LEADING_SHIFT 687
#define LEAVE 688
#define LEFT 689
#define LEFTLINE 690
#define LEFT_TEXT 691
#define LENGTH 692
#define LENGTH_OF 693
#define LENGTH_FUNC 694
#define LESS 695
#define LESS_OR_EQUAL 696
#define LEVEL_NUMBER 697
#define LIKE 698
#define LIMIT 699
#define LIMITS 700
#define LINAGE 701
#define LINAGE_COUNTER 702
#define LINE 703
#define LINE_COUNTER 704
#define LINE_LIMIT 705
#define LINE_SEQUENTIAL 706
#define LINES 707
#define LINES_AT_ROOT 708
#define LINKAGE 709
#define LIST_BOX 710
#define LITERAL 711
#define LM_RESIZE 712
#define LOC 713
#define LOCALE 714
#define LOCALE_DATE_FUNC 715
#define LOCALE_TIME_FUNC 716
#define LOCALE_TIME_FROM_FUNC 717
#define LOCAL_STORAGE 718
#define LOCK 719
#define LOCK_HOLDING 720
#define LONG_DATE 721
#define LOWER 722
#define LOWERED 723
#define LOWER_CASE_FUNC 724
#define LOWLIGHT 725
#define LOW_COLOR 726
#define LOW_VALUE 727
#define MAGNETIC_TAPE 728
#define MANUAL 729
#define MASS_UPDATE 730
#define MASTER_INDEX 731
#define MAX_LINES 732
#define MAX_PROGRESS 733
#define MAX_TEXT 734
#define MAX_VAL 735
#define MEMORY 736
#define MEDIUM_FONT 737
#define MENU 738
#define MERGE 739
#define MESSAGE 740
#define MINUS 741
#define MIN_VAL 742
#define MNEMONIC_NAME 743
#define MODE 744
#define MODIFY 745
#define MODULES 746
#define MOVE 747
#define MULTILINE 748
#define MULTIPLE 749
#define MULTIPLY 750
#define NAME 751
#define NAMED 752
#define NAMESPACE 753
#define NAMESPACE_PREFIX 754
#define NATIONAL 755
#define NATIONAL_EDITED 756
#define NATIONAL_OF_FUNC 757
#define NATIVE 758
#define NAVIGATE_URL 759
#define NEAREST_AWAY_FROM_ZERO 760
#define NEAREST_EVEN 761
#define NEAREST_TOWARD_ZERO 762
#define NEGATIVE 763
#define NESTED 764
#define NEW 765
#define NEXT 766
#define NEXT_ITEM 767
#define NEXT_GROUP 768
#define NEXT_PAGE 769
#define NO 770
#define NO_ADVANCING 771
#define NO_AUTOSEL 772
#define NO_AUTO_DEFAULT 773
#define NO_BOX 774
#define NO_DATA 775
#define NO_DIVIDERS 776
#define NO_ECHO 777
#define NO_F4 778
#define NO_FOCUS 779
#define NO_GROUP_TAB 780
#define NO_KEY_LETTER 781
#define NOMINAL 782
#define NO_SEARCH 783
#define NO_UPDOWN 784
#define NONNUMERIC 785
#define NORMAL 786
#define NOT 787
#define NOTAB 788
#define NOTHING 789
#define NOTIFY 790
#define NOTIFY_CHANGE 791
#define NOTIFY_DBLCLICK 792
#define NOTIFY_SELCHANGE 793
#define NOT_END 794
#define NOT_EOP 795
#define NOT_ESCAPE 796
#define NOT_EQUAL 797
#define NOT_EXCEPTION 798
#define NOT_INVALID_KEY 799
#define NOT_OVERFLOW 800
#define NOT_SIZE_ERROR 801
#define NUM_COL_HEADINGS 802
#define NUM_ROWS 803
#define NUMBER 804
#define NUMBERS 805
#define NUMERIC 806
#define NUMERIC_EDITED 807
#define NUMVALC_FUNC 808
#define OBJECT 809
#define OBJECT_COMPUTER 810
#define OCCURS 811
#define OF 812
#define OFF 813
#define OK_BUTTON 814
#define OMITTED 815
#define ON 816
#define ONLY 817
#define OPEN 818
#define OPTIONAL 819
#define OPTIONS 820
#define OR 821
#define ORDER 822
#define ORGANIZATION 823
#define OTHER 824
#define OTHERS 825
#define OUTPUT 826
#define OVERLAP_LEFT 827
#define OVERLAP_TOP 828
#define OVERLINE 829
#define PACKED_DECIMAL 830
#define PADDING 831
#define PASCAL 832
#define PAGE 833
#define PAGE_COUNTER 834
#define PAGE_SETUP 835
#define PAGED 836
#define PARAGRAPH 837
#define PARENT 838
#define PARSE 839
#define PASSWORD 840
#define PERFORM 841
#define PERMANENT 842
#define PH 843
#define PF 844
#define PHYSICAL 845
#define PICTURE 846
#define PICTURE_SYMBOL 847
#define PIXEL 848
#define PLACEMENT 849
#define PLUS 850
#define POINTER 851
#define POP_UP 852
#define POS 853
#define POSITION 854
#define POSITION_SHIFT 855
#define POSITIVE 856
#define PRESENT 857
#define PREVIOUS 858
#define PRINT 859
#define PRINT_CONTROL 860
#define PRINT_NO_PROMPT 861
#define PRINT_PREVIEW 862
#define PRINTER 863
#define PRINTER_1 864
#define PRINTING 865
#define PRIORITY 866
#define PROCEDURE 867
#define PROCEDURES 868
#define PROCEED 869
#define PROCESSING 870
#define PROGRAM 871
#define PROGRAM_ID 872
#define PROGRAM_NAME 873
#define PROGRAM_POINTER 874
#define PROGRESS 875
#define PROHIBITED 876
#define PROMPT 877
#define PROPERTIES 878
#define PROPERTY 879
#define PROTECTED 880
#define PURGE 881
#define PUSH_BUTTON 882
#define QUERY_INDEX 883
#define QUEUE 884
#define QUOTE 885
#define RADIO_BUTTON 886
#define RAISE 887
#define RAISED 888
#define RANDOM 889
#define RD 890
#define READ 891
#define READERS 892
#define READ_ONLY 893
#define READY_TRACE 894
#define RECEIVE 895
#define RECORD 896
#define RECORD_DATA 897
#define RECORD_OVERFLOW 898
#define RECORD_TO_ADD 899
#define RECORD_TO_DELETE 900
#define RECORDING 901
#define RECORDS 902
#define RECURSIVE 903
#define REDEFINES 904
#define REEL 905
#define REFERENCE 906
#define REFERENCES 907
#define REFRESH 908
#define REGION_COLOR 909
#define RELATIVE 910
#define RELEASE 911
#define REMAINDER 912
#define REMOVAL 913
#define RENAMES 914
#define REORG_CRITERIA 915
#define REPLACE 916
#define REPLACING 917
#define REPORT 918
#define REPORTING 919
#define REPORTS 920
#define REPOSITORY 921
#define REQUIRED 922
#define REREAD 923
#define RERUN 924
#define RESERVE 925
#define RESET 926
#define RESET_TRACE 927
#define RESET_GRID 928
#define RESET_LIST 929
#define RESET_TABS 930
#define RETRY 931
#define RETURN 932
#define RETURNING 933
#define REVERSE 934
#define REVERSE_FUNC 935
#define REVERSE_VIDEO 936
#define REVERSED 937
#define REWIND 938
#define REWRITE 939
#define RF 940
#define RH 941
#define RIGHT 942
#define RIGHT_ALIGN 943
#define RIMMED 944
#define ROLLBACK 945
#define ROUNDED 946
#define ROUNDING 947
#define ROW_COLOR 948
#define ROW_COLOR_PATTERN 949
#define ROW_DIVIDERS 950
#define ROW_FONT 951
#define ROW_HEADINGS 952
#define ROW_PROTECTION 953
#define RUN 954
#define S 955
#define SAME 956
#define SAVE_AS 957
#define SAVE_AS_NO_PROMPT 958
#define SCREEN 959
#define SCREEN_CONTROL 960
#define SCROLL 961
#define SCROLL_BAR 962
#define SD 963
#define SEARCH 964
#define SEARCH_OPTIONS 965
#define SEARCH_TEXT 966
#define SECONDS 967
#define SECTION 968
#define SECURE 969
#define SEGMENT 970
#define SEGMENT_LIMIT 971
#define SELECT 972
#define SELECTION_INDEX 973
#define SELECTION_TEXT 974
#define SELECT_ALL 975
#define SELF_ACT 976
#define SEMI_COLON 977
#define SEND 978
#define SENTENCE 979
#define SEPARATE 980
#define SEPARATION 981
#define SEQUENCE 982
#define SEQUENTIAL 983
#define SET 984
#define SEVENTY_EIGHT 985
#define SHADING 986
#define SHADOW 987
#define SHARING 988
#define SHORT_DATE 989
#define SHOW_LINES 990
#define SHOW_NONE 991
#define SHOW_SEL_ALWAYS 992
#define SIGN 993
#define SIGNED 994
#define SIGNED_INT 995
#define SIGNED_LONG 996
#define SIGNED_SHORT 997
#define SIXTY_SIX 998
#define SIZE 999
#define SIZE_ERROR 1000
#define SMALL_FONT 1001
#define SORT 1002
#define SORT_MERGE 1003
#define SORT_ORDER 1004
#define SOURCE 1005
#define SOURCE_COMPUTER 1006
#define SPACE 1007
#define SPECIAL_NAMES 1008
#define SPINNER 1009
#define SQUARE 1010
#define STANDARD 1011
#define STANDARD_1 1012
#define STANDARD_2 1013
#define STANDARD_BINARY 1014
#define STANDARD_DECIMAL 1015
#define START 1016
#define START_X 1017
#define START_Y 1018
#define STATIC 1019
#define STATIC_LIST 1020
#define STATUS 1021
#define STATUS_BAR 1022
#define STATUS_TEXT 1023
#define STDCALL 1024
#define STEP 1025
#define STOP 1026
#define STRING 1027
#define STRONG 1028
#define STYLE 1029
#define SUB_QUEUE_1 1030
#define SUB_QUEUE_2 1031
#define SUB_QUEUE_3 1032
#define SUBSTITUTE_FUNC 1033
#define SUBSTITUTE_CASE_FUNC 1034
#define SUBTRACT 1035
#define SUBWINDOW 1036
#define SUM 1037
#define SUPPRESS 1038
#define SUPPRESS_XML 1039
#define SYMBOLIC 1040
#define SYNCHRONIZED 1041
#define SYSTEM_DEFAULT 1042
#define SYSTEM_INFO 1043
#define SYSTEM_OFFSET 1044
#define TAB 1045
#define TAB_TO_ADD 1046
#define TAB_TO_DELETE 1047
#define TABLE 1048
#define TALLYING 1049
#define TEMPORARY 1050
#define TAPE 1051
#define TERMINAL 1052
#define TERMINATE 1053
#define TERMINAL_INFO 1054
#define TERMINATION_VALUE 1055
#define TEST 1056
#define TEXT 1057
#define THAN 1058
#define THEN 1059
#define THREAD 1060
#define THREADS 1061
#define THRU 1062
#define THUMB_POSITION 1063
#define TILED_HEADINGS 1064
#define TIME 1065
#define TIME_OUT 1066
#define TIMES 1067
#define TITLE 1068
#define TITLE_POSITION 1069
#define TO 1070
#define TOK_AMPER 1071
#define TOK_CLOSE_PAREN 1072
#define TOK_COLON 1073
#define TOK_DIV 1074
#define TOK_DOT 1075
#define TOK_EQUAL 1076
#define TOK_EXTERN 1077
#define TOK_FALSE 1078
#define TOK_FILE 1079
#define TOK_GREATER 1080
#define TOK_INITIAL 1081
#define TOK_LESS 1082
#define TOK_MINUS 1083
#define TOK_MUL 1084
#define TOK_NULL 1085
#define TOK_OVERFLOW 1086
#define TOK_OPEN_PAREN 1087
#define TOK_PLUS 1088
#define TOK_TRUE 1089
#define TOP 1090
#define TOWARD_GREATER 1091
#define TOWARD_LESSER 1092
#define TRACK 1093
#define TRACKS 1094
#define TRACK_AREA 1095
#define TRACK_LIMIT 1096
#define TRADITIONAL_FONT 1097
#define TRAILING 1098
#define TRAILING_SHIFT 1099
#define TRANSFORM 1100
#define TRANSPARENT 1101
#define TREE_VIEW 1102
#define TRIM_FUNC 1103
#define TRUNCATION 1104
#define TYPE 1105
#define TYPEDEF 1106
#define U 1107
#define UCS_4 1108
#define UNBOUNDED 1109
#define UNDERLINE 1110
#define UNFRAMED 1111
#define UNIT 1112
#define UNLOCK 1113
#define UNSIGNED 1114
#define UNSIGNED_INT 1115
#define UNSIGNED_LONG 1116
#define UNSIGNED_SHORT 1117
#define UNSORTED 1118
#define UNSTRING 1119
#define UNTIL 1120
#define UP 1121
#define UPDATE 1122
#define UPDATERS 1123
#define UPON 1124
#define UPON_ARGUMENT_NUMBER 1125
#define UPON_COMMAND_LINE 1126
#define UPON_ENVIRONMENT_NAME 1127
#define UPON_ENVIRONMENT_VALUE 1128
#define UPPER 1129
#define UPPER_CASE_FUNC 1130
#define USAGE 1131
#define USE 1132
#define USE_ALT 1133
#define USE_RETURN 1134
#define USE_TAB 1135
#define USER 1136
#define USER_DEFAULT 1137
#define USER_FUNCTION_NAME 1138
#define USING 1139
#define UTF_8 1140
#define UTF_16 1141
#define V 1142
#define VALIDATE 1143
#define VALIDATING 1144
#define VALUE 1145
#define VALUE_FORMAT 1146
#define VARIABLE 1147
#define VARIANT 1148
#define VARYING 1149
#define VERTICAL 1150
#define VERY_HEAVY 1151
#define VIRTUAL_WIDTH 1152
#define VOLATILE 1153
#define VPADDING 1154
#define VSCROLL 1155
#define VSCROLL_BAR 1156
#define VSCROLL_POS 1157
#define VTOP 1158
#define WAIT 1159
#define WEB_BROWSER 1160
#define WHEN 1161
#define WHEN_COMPILED_FUNC 1162
#define WHEN_XML 1163
#define WIDTH 1164
#define WIDTH_IN_CELLS 1165
#define WINDOW 1166
#define WITH 1167
#define WORD 1168
#define WORDS 1169
#define WORKING_STORAGE 1170
#define WRAP 1171
#define WRITE 1172
#define WRITE_ONLY 1173
#define WRITE_VERIFY 1174
#define WRITERS 1175
#define X 1176
#define XML 1177
#define XML_DECLARATION 1178
#define Y 1179
#define YYYYDDD 1180
#define YYYYMMDD 1181
#define ZERO 1182
#define SHIFT_PREFER 1183

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_H_INCLUDED  */
