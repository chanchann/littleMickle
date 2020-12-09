/* 
使用detach分离线程会让线程在后台运行，线程分离后与主线程无法直接交互，也不能被join

std::thread t(f);
t.detach();
assert(!t.joinable()); // 因此joinable为true才能join或detach

分离线程称为守护线程，即没有任何显式接口并运行在后台的线程，其特点是长时间运行。
比如有一个文档处理应用，为了同时编辑多个文档，每次打开一个新文档则可以开一个分离线程


void edit_document(const std::string& filename) {
    open_document_and_display_gui(filename);
    while (!done_editing()) {
        user_command cmd=get_user_input();
        if (cmd.type == open_new_document) {
            const std::string new_name = get_filename_from_user();
            std::thread t(edit_document, new_name);
            t.detach();
        } else {
            process_user_input(cmd);
        }
    }
}
*/



