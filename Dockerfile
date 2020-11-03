# -- Dockerfile --
# 这个文件负责构建包含你的程序的 Docker 容器

# 使用 Java 12
FROM gcc:10
WORKDIR /app/
# 向容器内复制文件
COPY ./* ./
# 编译程序
RUN gcc Homework03.c -o Homework03
RUN chmod +x Homework03