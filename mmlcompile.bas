FUNCTION CompileMML$ (mml AS STRING)
    DIM AS _UNSIGNED LONG i
    DIM AS _UNSIGNED INTEGER notedelay, freqptr, cmdptr, freq_end, cmd_end
    DIM AS _UNSIGNED _BYTE octave, channel, nextispoly

    DIM AS _UNSIGNED LONG freqs(1024)
    DIM AS _BYTE cmds(124)
    cmds$ = ""
    freqs$ = ""
    FOR i = 1 TO LEN(mml)

        SELECT CASE MID$(mml, i, 1)
            CASE "a" TO "g", "n"
                IF nextispoly THEN
                    channel = channel + 1
                    nextispoly = 0
                ELSE channel = 0
                    cmds(cmdptr) = -1 'insert delay
                    freqs(freqptr) = notedelay
                    cmdptr = cmdptr + 1: freqptr = freqptr + 1
                END IF
                cmds(cmdptr) = channel
                freqs(freqptr) = SemitoneToFreq(NoteToSemitone(MID$(mml, i), octave, i))
                cmdptr = cmdptr + 1: freqptr = freqptr + 1

            CASE ">": octave = octave + 1
            CASE "<": octave = octave - 1
            CASE "o": octave = VAL(MID$(mml, i + 1, 1))
            CASE ",": nextispoly = 1
        END SELECT

    NEXT

    freq_end = freqptr: cmd_end = cmdptr
    freqptr = 0
    FOR i = 0 TO cmd_end
        SELECT CASE cmds(i)
            CASE IS >= 0: freqptr = freqptr + 1

            CASE -1
                freqptr = freqptr + 1
                IF cmds(i - 1) = -1 THEN
                    cmds(i - 1) = -127 'no op w/arg
                    freqs(freqptr) = freqs(freqptr) + freqs(freqptr - 1)
                END IF
        END SELECT
    NEXT

    freqptr = 0
    FOR i = 0 TO cmd_end
        SELECT CASE cmds(i)
            CASE IS >= 0: freqptr = freqptr + 1
        END SELECT
    NEXT

    'CompileMML = "char song_commands[] = {" + cmds$ + "};" + CHR$(13) + "unsigned int song_values[] = {" + freqs$ + "};"
END FUNCTION

FUNCTION IsNum~%% (n AS STRING)
    IsNum = _TRIM$(STR$(VAL(n))) = n
END FUNCTION

FUNCTION NoteToSemitone~%% (n AS STRING, o AS _UNSIGNED _BYTE, i AS _UNSIGNED LONG)
    IF LEFT$(n, 1) = "n" THEN
        n~%% = VAL(MID$(n, 2))
        i = i + LEN(STR$(n~%%))
        NoteToSemitone = n~%%
    ELSE
        DIM l AS _UNSIGNED LONG, no AS _UNSIGNED _BYTE
        l = 1
        no = o
        SELECT CASE LEFT$(n, 1)
            CASE "c": n~%% = 1
            CASE "d": n~%% = 3
            CASE "e": n~%% = 5
            CASE "f": n~%% = 6
            CASE "g": n~%% = 8
            CASE "a": n~%% = 10
            CASE "b": n~%% = 12
        END SELECT

        SELECT CASE MID$(n, 2, 1)
            CASE "-": n~%% = n~%% - 1
            CASE "+", "#": n~%% = n~%% + 1
        END SELECT

        IF IsNum(MID$(n, 2, 1)) THEN
            no = VAL(MID$(n, 2, 1))
            l = 2
        ELSEIF IsNum(MID$(n, 3, 1)) THEN
            no = VAL(MID$(n, 3, 1))
            l = 3
        END IF

        i = i + l

        NoteToSemitone = (n~%% + (no * 12)) - 9
    END IF
END FUNCTION

FUNCTION SemitoneToFreq## (s AS _UNSIGNED INTEGER)
    SemitoneToFreq = 2 ^ ((s - 49) / 12) * 440
END FUNCTION
