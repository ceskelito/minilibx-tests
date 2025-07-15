include variables.mk

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

deepclean: clean
	$(MAKE) -C clean $(IMGLIB_DIR)
	$(MAKE) -C clean $(COLORS_DIR)
	$(MAKE) -C clean $(MLXLIB_DIR)

deepfclean: fclean
	$(MAKE) -C fclean $(IMGLIB_DIR)
	$(MAKE) -C fclean $(COLORS_DIR)
	$(MAKE) -C clean $(MLXLIB_DIR) # MLX's make doesn't have fclean rule

.PHONY: clean fclean deepclean deepfclean
	
