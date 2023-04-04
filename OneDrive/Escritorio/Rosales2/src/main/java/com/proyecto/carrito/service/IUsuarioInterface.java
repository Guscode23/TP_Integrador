package com.proyecto.carrito.service;

import java.util.List;
import java.util.Optional;

import org.springframework.data.jpa.repository.JpaRepository;

import com.proyecto.carrito.model.Cliente;


public interface IUsuarioInterface extends JpaRepository<Cliente, Integer>{ // faltaba el extends
	List<Cliente> findAll();
	Optional<Cliente> findById(Integer id);
	Cliente save (Cliente usuario);
	Optional<Cliente> findByEmail(String email);

}
