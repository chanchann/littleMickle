// 编译期switch
//

using ChooseResult = CompileTimeSwitch<std::integer_sequence<bool, Cond1, ..., CondN>,
                                       Cont<Res1, ..., ResN(, Def)>
                    >;
